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
#include "ITs-location-manager-common.h"

/** @addtogroup itc-location-manager
*  @ingroup itc
*  @{
*/

//& set: LocationManager

//Callbacks

/**
* @function			LocationPositionUpdatedCB
* @description		Called periodically with updated position information
* @parameter		double latitude, double longitude, double altitude, time_t timestamp, void *user_data
* @return			NA
*/
static void LocationPositionUpdatedCB(double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationPositionUpdatedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationVelocityUpdatedCB
* @description		Called periodically with updated velocity information
* @parameter		double speed, double direction, double climb, time_t timestamp, void *user_data
* @return			NA
*/
static void LocationVelocityUpdatedCB(double speed, double direction, double climb, time_t timestamp, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationVelocityUpdatedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationZoneChangedCB
* @description		Called when the user defined zones are entered or left.
* @parameter		location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp, void *user_data
* @return			NA
*/
static void LocationZoneChangedCB(location_boundary_state_e state, double latitude, double longitude, double altitude, time_t timestamp, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationZoneChangedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationServiceStateChangeCb
* @description		Called when state is changed
* @parameter		location_service_state_e state, void *user_data
* @return			NA
*/
void LocationServiceStateChangeCb(location_service_state_e state, void *user_data)
{
	g_bCallbackReturnValue = false;
//#if DEBUG
	FPRINTF("[Line : %d][%s] LocationServiceStateChangeCb callback called\\n", __LINE__, API_NAMESPACE);
//#endif
	g_bCallbackHit = true;
	g_bIsServiceEnabled = false;
	switch ( state )
	{
	case LOCATIONS_SERVICE_DISABLED:
		FPRINTF("[Line : %d][%s] Service State: LOCATIONS_SERVICE_DISABLED\\n", __LINE__, API_NAMESPACE);
		g_bIsServiceEnabled = false;
		g_bCallbackReturnValue = true;
		break;
	case LOCATIONS_SERVICE_ENABLED:
		FPRINTF("[Line : %d][%s] Service State: LOCATIONS_SERVICE_ENABLED\\n", __LINE__, API_NAMESPACE);
		g_bIsServiceEnabled = true;
		g_bCallbackReturnValue = true;
		break;
	}
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationServiceMethodStateChangeCb
* @description		Called when state is changed
* @parameter		location_service_state_e state, void *user_data
* @return			NA
*/
void LocationServiceMethodStateChangeCb(location_service_state_e state, void *user_data)
{
	g_bCallbackReturnValue = false;
//#if DEBUG
	FPRINTF("[Line : %d][%s] LocationServiceMethodStateChangeCb callback called\\n", __LINE__, API_NAMESPACE);
//#endif
	g_bCallbackHit = true;
	g_bIsServiceEnabled = false;

	switch ( state )
	{
	case LOCATIONS_SERVICE_DISABLED:
		FPRINTF("[Line : %d][%s] Service State: LOCATIONS_SERVICE_DISABLED\\n", __LINE__, API_NAMESPACE);
		g_bIsServiceEnabled = false;
		g_bCallbackReturnValue = true;
		break;
	case LOCATIONS_SERVICE_ENABLED:
		FPRINTF("[Line : %d][%s] Service State: LOCATIONS_SERVICE_ENABLED\\n", __LINE__, API_NAMESPACE);
		g_bIsServiceEnabled = true;
		g_bCallbackReturnValue = true;
		break;
	}
	if ((g_pLocationManagerMainLoop != NULL) && (g_bIsSatelliteEnabled == true))
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationBoundsCB
* @description		Called iteratively to notify you of location bounds
* @parameter		location_bounds_h bounds, void *user_data
* @return			NA
*/
static bool LocationBoundsCB(location_bounds_h bounds, void *user_data)
{
	g_bCallbackReturnValue = false;
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationBoundsCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( bounds == NULL )
	{
		FPRINTF("[Line : %d][%s] LocationBoundsCB callback returned null bounds\\n", __LINE__, API_NAMESPACE);
		g_bCallbackReturnValue = false;
	}
	else
	{
		g_bCallbackReturnValue = true;
	}
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return false;
}

/**
* @function			LocationSettingChangedCB
* @description		Called when the user defined zones are entered or exited.
* @parameter		location_method_e method, bool enable, void *user_data
* @return			NA
*/
static void LocationSettingChangedCB(location_method_e method, bool enable, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationSettingChangedCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			LocationUpdatedCB
* @description		Called at defined interval with updated location information
* @parameter		location_error_e error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double direction, double climb, void *user_data
* @return			NA
*/
static void LocationUpdatedCB(location_error_e error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double direction, double climb, void *user_data)
{
#if DEBUG
FPRINTF("[Line : %d][%s] LocationUpdatedCB callback called. error=[%d]\\n", __LINE__, API_NAMESPACE, error);
#endif
	g_bCallbackHit = true;
	if ( error ) {
		g_bCallbackReturnValue = false;
	}
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/*
 * @function		LocationChangedCB
 * @description		Called at defined interval with updated location information.
 * @parameter		double latitude, double longitude, double altitude, double speed, double direction, double horizontal_accuracy, time_t timestamp, void *user_data
 * @return			NA
 */
static void LocationChangedCB(double latitude, double longitude, double altitude, double speed, double direction, double horizontal_accuracy, time_t timestamp, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] LocationChangedCB callback called\\n", __LINE__ ,API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}

/**
* @function			ITs_location_manager_startup
* @description		Called before each test, set the service boolean true
* @parameter		NA
* @return			NA
*/
void ITs_location_manager_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCleanupNotRequired = false;
	g_bIsWpsFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_WPS_FEATURE, API_NAMESPACE);
	g_bIsGpsFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_GPS_FEATURE, API_NAMESPACE);
	g_bIsLocationFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_FEATURE, API_NAMESPACE);

	g_bIsLocationManagerSupported =  g_bIsLocationFeatureSupported && ( g_bIsWpsFeatureSupported || g_bIsGpsFeatureSupported);
	g_bLocationMismatch = false;
	g_bLocationNotSupported = false;
	LocationManagerCreateStart(&g_stManager);
}

/**
* @function			ITs_location_manager_cleanup
* @description		Called after each test
* @parameter		NA
* @return			NA
*/
void ITs_location_manager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bCleanupNotRequired != true )
	{
		LocationManagerStopDestroy(&g_stManager);
	}
	return;
}

/** @addtogroup itc-location-manager-testcases
*  @brief		Integration testcases for module location-manager
*  @ingroup		itc-location-manager
*  @{
*/

//& purpose: Starts/stops the location service.
//& type: auto

/**
* @testcase				ITc_location_manager_start_stop_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Starts/stops the location service.
* @scenario				Create location manager\n
*						Start location service\n
*						Stop the location service\n
*						Destroy location manager
* @apicovered			location_manager_start, location_manager_stop
* @passcase				When location_manager_start and location_manager_stop are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		It invokes location_position_updated_cb, location_velocity_updated_cb, location_zone_changed_cb, and location_service_state_changed_cb
*/
int ITc_location_manager_start_stop_p(void)
{
	START_TEST_MANAGER;

	LocationManagerStopDestroy(&g_stManager);
	g_bCleanupNotRequired = true;

	int nTimeoutId = 0;
	location_manager_h stManager = {0};
	location_error_e nRet = location_manager_create(LOCATIONS_METHOD_HYBRID, &stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
	CHECK_HANDLE(stManager,"location_manager_create");

	nRet = location_manager_set_service_state_changed_cb(stManager, LocationServiceStateChangeCb, NULL);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_service_state_changed_cb", LocationManagerGetError(nRet), location_manager_destroy(stManager));

	g_bCallbackHit = false;

	// Target API
	nRet = location_manager_start(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_start", LocationManagerGetError(nRet), location_manager_unset_service_state_changed_cb(stManager);location_manager_destroy(stManager));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] location_manager_start Callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_bIsServiceEnabled != true)
	{
		FPRINTF("[Line : %d][%s] location_manager_start failed  g_bIsServiceEnabled is false \\n", __LINE__, API_NAMESPACE);
		location_manager_unset_service_state_changed_cb(stManager);
		location_manager_destroy(stManager);
		return 1;
	}

	g_bCallbackHit = false;
	// Target API
	nRet = location_manager_stop(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_stop", LocationManagerGetError(nRet), location_manager_unset_service_state_changed_cb(stManager);location_manager_destroy(stManager));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] location_manager_stop Callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(g_bIsServiceEnabled != false)
	{
		FPRINTF("[Line : %d][%s] location_manager_stop failed  g_bIsServiceEnabled is false \\n", __LINE__, API_NAMESPACE);
		location_manager_unset_service_state_changed_cb(stManager);
		location_manager_destroy(stManager);
		return 1;
	}

	nRet =  location_manager_unset_service_state_changed_cb(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_service_state_changed_cb", LocationManagerGetError(nRet), location_manager_destroy(stManager));

	nRet = location_manager_destroy(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_destroy", LocationManagerGetError(nRet), location_manager_destroy(stManager));

	return 0;
}

//& purpose: Api to test location_manager_create and location_manager_destroy
//& type: auto

/**
* @testcase				ITc_location_manager_create_destroy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Create location manager and destroy it
* @scenario				Create manager\n
*						Destroy manager
* @apicovered			location_manager_create, location_manager_destroy
* @passcase				When location_manager_create and location_manager_destroy are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_manager_create_destroy_p(void)
{
	START_TEST_MANAGER;

	location_manager_h stManager = {0};
	location_method_e eTestLocationMethod = -1;
	location_method_e location_method[] = {
		LOCATIONS_METHOD_GPS,
		LOCATIONS_METHOD_WPS,
		LOCATIONS_METHOD_HYBRID,
		LOCATIONS_METHOD_PASSIVE,
	};

	int nEnumSize = sizeof(location_method) / sizeof(location_method[0]);
	int nEnumCounter = 0;

	LocationManagerStopDestroy(&g_stManager);
	g_bCleanupNotRequired = true;

	for ( nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		eTestLocationMethod = -1;
		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_WPS )
		{
			if ( g_bIsLocationFeatureSupported && g_bIsWpsFeatureSupported )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_GPS )
		{
			if ( g_bIsLocationFeatureSupported && g_bIsGpsFeatureSupported )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_HYBRID )
		{
			if ( g_bIsLocationFeatureSupported && ( g_bIsGpsFeatureSupported || g_bIsWpsFeatureSupported))
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}
		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_PASSIVE )
		{
			if ( g_bIsLocationFeatureSupported )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		// Target API
		location_error_e nRet = location_manager_create(location_method[nEnumCounter], &stManager);
		if ( eTestLocationMethod == -1 )
		{
			if ( nRet != LOCATIONS_ERROR_NOT_SUPPORTED )
			{
				FPRINTF("[Line : %d][%s] location_manager_create failed for unsupported Enum %s, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetEnum(location_method[nEnumCounter]), LocationManagerGetError(nRet));
				return 1;
			}

			FPRINTF("[Line : %d][%s] location_manager_create is unsupported for enum %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetEnum(location_method[nEnumCounter]));
			continue;
		}
		else
		{
			PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
		}

		CHECK_HANDLE(stManager,"location_manager_create");
		// Target API
		nRet = location_manager_destroy(stManager);
		PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_destroy", LocationManagerGetError(nRet));
	}

	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked when the location service state is changed.
//& type: auto

/**
* @testcase				ITc_location_manager_set_unset_service_state_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Registers/Unregisters a callback function to be invoked when the location service state is changed.
* @scenario				Registers a callback function to be invoked when the location service state is changed\n
*						Check if callback is invoked\n
*						Unregisters the callback function
* @apicovered			location_manager_set_service_state_changed_cb, location_manager_unset_service_state_changed_cb
* @passcase				When location_manager_set_service_state_changed_cb and location_manager_unset_service_state_changed_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_service_state_changed_cb() will be invoked
*/
int ITc_location_manager_set_unset_service_state_changed_cb_p(void)
{
	START_TEST_MANAGER;

	LocationManagerStopDestroy(&g_stManager);
	g_bCleanupNotRequired = true;

	int nTimeoutId = 0;
	location_manager_h stManager = {0};
	location_error_e nRet = location_manager_create(LOCATIONS_METHOD_HYBRID, &stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
	CHECK_HANDLE(stManager,"location_manager_create");

	// Target API
	nRet = location_manager_set_service_state_changed_cb(stManager, LocationServiceStateChangeCb, NULL);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_service_state_changed_cb", LocationManagerGetError(nRet), location_manager_destroy(stManager));

	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;

	//check using callback for start
	nRet = location_manager_start(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_start", LocationManagerGetError(nRet), location_manager_unset_service_state_changed_cb(stManager);location_manager_destroy(stManager));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] location_manager_start Callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	if(g_bIsServiceEnabled != true)
	{
		FPRINTF("[Line : %d][%s] location_manager_start failed  g_bIsServiceEnabled is false \\n", __LINE__, API_NAMESPACE);
		location_manager_unset_service_state_changed_cb(stManager);
		location_manager_destroy(stManager);
		return 1;
	}

	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;

	//check using callback for stop
	nRet = location_manager_stop(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_stop", LocationManagerGetError(nRet), location_manager_unset_service_state_changed_cb(stManager);location_manager_destroy(stManager));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] location_manager_stop Callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	if(g_bIsServiceEnabled != false)
	{
		FPRINTF("[Line : %d][%s] location_manager_stop failed  g_bIsServiceEnabled is false \\n", __LINE__, API_NAMESPACE);
		location_manager_unset_service_state_changed_cb(stManager);
		location_manager_destroy(stManager);
		return 1;
	}

	nRet =  location_manager_unset_service_state_changed_cb(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_service_state_changed_cb", LocationManagerGetError(nRet), location_manager_destroy(stManager));

	nRet = location_manager_destroy(stManager);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_destroy", LocationManagerGetError(nRet), location_manager_destroy(stManager));
	return 0;
}

//& purpose: Gets the current accuracy information
//& type: auto

/**
* @testcase				ITc_location_manager_get_accuracy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the current accuracy information
* @scenario				Create and start location manager\n
*						Get the current accuracy information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_accuracy
* @passcase				When location_manager_get_accuracy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_manager_get_accuracy_p(void)
{
	START_TEST_MANAGER;

	location_accuracy_level_e level;
	double dbHorizontal = 0, dbHertical = 0;

	// Target API
	location_error_e nRet = location_manager_get_accuracy(g_stManager, &level, &dbHorizontal, &dbHertical);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_accuracy", LocationManagerGetError(nRet));
	if ( level == LOCATIONS_ACCURACY_NONE )
	{
		FPRINTF("[Line : %d][%s] Invalid level data\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the distance in meters between two locations.
//& type: auto

/**
* @testcase				ITc_location_manager_get_distance_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the distance in meters between two locations.
* @scenario				Create and start location manager\n
*						Get the distance in meters between two locations\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_distance
* @passcase				When location_manager_get_distance is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_manager_get_distance_p(void)
{
	START_TEST_MANAGER;

	double dbStartLatitude = 20, dbStartLongitude= 26, dbEndLatitude = -20, dbEndLongitude = -26;
	double dbDistance = 0;

	// Target API
	location_error_e nRet = location_manager_get_distance(dbStartLatitude, dbStartLongitude, dbEndLatitude, dbEndLongitude, &dbDistance);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_distance", LocationManagerGetError(nRet));
	if ( dbDistance == 0 )
	{
		FPRINTF("[Line : %d][%s] Distance returned = %f\\n", __LINE__, API_NAMESPACE, dbDistance);
		return 1;
	}

	return 0;
}

//& purpose: Gets the last recorded accuracy information
//& type: auto

/**
* @testcase				ITc_location_manager_get_last_accuracy_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the last recorded accuracy information
* @scenario				Create and start location manager\n
*						Get the last recorded accuracy information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_last_accuracy
* @passcase				When location_manager_get_last_accuracy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location manager's handle must be created by location_manager_create()
* @postcondition		None
*/
int ITc_location_manager_get_last_accuracy_p(void)
{
	START_TEST_MANAGER;

	location_accuracy_level_e level;
	double dbHorizontal = 0, dbHertical = 0;

	// Target API
	location_error_e nRet = location_manager_get_last_accuracy(g_stManager, &level, &dbHorizontal, &dbHertical);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_last_accuracy", LocationManagerGetError(nRet));

	if ( level == LOCATIONS_ACCURACY_NONE )
	{
		FPRINTF("[Line : %d][%s] Invalid level data\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the last location information
//& type: auto

/**
* @testcase				ITc_location_manager_get_last_location_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the last location information
* @scenario				Create and start location manager\n
*						Get the last location information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_last_location
* @passcase				When location_manager_get_last_location is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location manager's handle must be created by location_manager_create()
* @postcondition		None
*/
int ITc_location_manager_get_last_location_p(void)
{
	START_TEST_MANAGER;

	location_accuracy_level_e level;
	double dbAltitute, dbLatitude, dbLongitude, dbClimb, dbDirection, dbSpeed, dbHorizontal, dbVertical;
	time_t timestamp;

	// Target API
	location_error_e nRet = location_manager_get_last_location(g_stManager, &dbAltitute, &dbLatitude, &dbLongitude, &dbClimb, &dbDirection, &dbSpeed, &level, &dbHorizontal, &dbVertical, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_last_location", LocationManagerGetError(nRet));
	if ( level == LOCATIONS_ACCURACY_NONE )
	{
		FPRINTF("[Line : %d][%s] Invalid level data\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the last recorded position information
//& type: auto

/**
* @testcase				ITc_location_manager_get_last_position_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the last recorded position information
* @scenario				Create and start location manager\n
*						Get the last recorded position information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_last_position
* @passcase				When location_manager_get_last_position is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location manager's handle must be created by location_manager_create()
* @postcondition		None
*/
int ITc_location_manager_get_last_position_p(void)
{
	START_TEST_MANAGER;

	double dbAltitute, dbLatitude, dbLongitude;
	time_t timestamp;

	// Target API
	location_error_e nRet = location_manager_get_last_position(g_stManager, &dbAltitute, &dbLatitude, &dbLongitude, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_last_position", LocationManagerGetError(nRet));
	if ( timestamp == 0 )
	{
		FPRINTF("[Line : %d][%s] Invalid timestamp\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the last recorded velocity information
//& type: auto

/**
* @testcase				ITc_location_manager_get_last_velocity_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the last recorded velocity information
* @scenario				Create and start location manager\n
*						Get the last recorded velocity information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_last_velocity
* @passcase				When location_manager_get_last_velocity is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location manager's handle must be created by location_manager_create()
* @postcondition		None
*/
int ITc_location_manager_get_last_velocity_p(void)
{
	START_TEST_MANAGER;

	double dbClimb, dbDirection, dbSpeed;
	time_t timestamp;

	// Target API
	location_error_e nRet = location_manager_get_last_velocity(g_stManager, &dbClimb, &dbDirection, &dbSpeed, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_last_velocity", LocationManagerGetError(nRet));
	if ( timestamp == 0 )
	{
		FPRINTF("[Line : %d][%s] Invalid timestamp\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the current position information
//& type: auto

/**
* @testcase				ITc_location_manager_get_location_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the current position information
* @scenario				Create and start location manager\n
*						Get the current position information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_location
* @passcase				When location_manager_get_location is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_manager_get_location_p(void)
{
	START_TEST_MANAGER;

	location_accuracy_level_e level	;
	double dbAltitute, dbLatitude, dbLongitude, dbClimb, dbDirection, dbSpeed, dbHorizontal, dbVertical;
	time_t timestamp;

	// Target API
	location_error_e nRet = location_manager_get_location(g_stManager, &dbAltitute, &dbLatitude, &dbLongitude, &dbClimb, &dbDirection, &dbSpeed, &level, &dbHorizontal, &dbVertical, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_location", LocationManagerGetError(nRet));

	if ( level == LOCATIONS_ACCURACY_NONE )
	{
		FPRINTF("[Line : %d][%s] Invalid level data\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets/checks the given location manager's method.
//& type: auto

/**
* @testcase				ITc_location_manager_get_is_supported_method_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets/checks the given location manager's method.
* @scenario				Create and start location manager\n
*						Get the given location manager's method\n
*						Checks whether the given location method is available or not\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_method	, location_manager_is_supported_method
* @passcase				When location_manager_get_method, location_manager_is_supported_method are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location manager's handle must be created by location_manager_create()
* @postcondition		None
*/
int ITc_location_manager_get_is_supported_method_p(void)
{
	START_TEST_MANAGER;
	location_method_e method;

	// Target API
	location_error_e nRet = location_manager_get_method(g_stManager, &method);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_method", LocationManagerGetError(nRet));

	// Target API
	bool isSupported = location_manager_is_supported_method(method);
	if ( isSupported != true )
	{
		FPRINTF("[Line : %d][%s] location_manager_is_supported_method failed, returned isSupported = %d\\n", __LINE__, API_NAMESPACE, isSupported);
		return 1;
	}

	return 0;
}

//& purpose: Gets the current position information
//& type: auto

/**
* @testcase				ITc_location_manager_get_position_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the current position information
* @scenario				Create and start location manager\n
*						Get the current position information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_position
* @passcase				When location_manager_get_position is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_manager_get_position_p(void)
{
	START_TEST_MANAGER;

	double dbAltitute, dbLatitude, dbLongitude;
	time_t timestamp;

	// Target API
	location_error_e nRet = location_manager_get_position(g_stManager, &dbAltitute, &dbLatitude, &dbLongitude, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_position", LocationManagerGetError(nRet));
	if ( timestamp < 0 )
	{
		FPRINTF("[Line : %d][%s] Invalid timestamp\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Gets the current position information
//& type: auto

/**
* @testcase				ITc_location_manager_get_velocity_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Gets the current position information
* @scenario				Create and start location manager\n
*						Get the current position information\n
*						Stop and Destroy location manager
* @apicovered			location_manager_get_velocity
* @passcase				When location_manager_get_velocity is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_manager_get_velocity_p(void)
{
	START_TEST_MANAGER;

	double dbClimb, dbDirection, dbSpeed;
	time_t timestamp;
	g_bCallbackHit = false;

	// Target API
	location_error_e nRet = location_manager_get_velocity(g_stManager, &dbClimb, &dbDirection, &dbSpeed, &timestamp);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_velocity", LocationManagerGetError(nRet));
	if ( timestamp < 0 )
	{
		FPRINTF("[Line : %d][%s] Invalid timestamp\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Adds/Removes bounds for a given location manager.
//& type: auto

/**
* @testcase				ITc_location_manager_add_remove_boundary_circle_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Adds/Removes bounds for a given location manager.
* @scenario				Adds bounds for a given location manager\n
*						Deletes bounds for a given location manager.
* @apicovered			location_manager_add_boundary, location_manager_remove_boundary
* @passcase				When location_manager_add_boundary and location_manager_remove_boundary are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		It invokes location_manager_set_zone_changed_cb() when a boundary is entered or left, if you set a callback with location_manager_set_zone_changed_cb
* @remarks				Callback is not checked, as callback checking is manual
*/
int ITc_location_manager_add_remove_boundary_circle_p(void)
{
	START_TEST_MANAGER;

	//Add the circle bounds
	location_bounds_h bounds_circle;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;

	location_bound_error_e nRet1 = location_bounds_create_circle(center, radius, &bounds_circle);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_create_circle", LocationBoundsGetError(nRet1));

	// Target API
	location_error_e nRet = location_manager_add_boundary(g_stManager, bounds_circle);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_add_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_circle));

	// Target API
	nRet = location_manager_remove_boundary(g_stManager, bounds_circle);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_remove_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_circle));

	nRet1 = location_bounds_destroy(bounds_circle);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_destroy", LocationBoundsGetError(nRet1));

	return 0;
}


//& purpose: Adds/Removes bounds for a given location manager.
//& type: auto

/**
* @testcase				ITc_location_manager_add_remove_boundary_rect_p
* @since_tizen			2.3
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Adds/Removes bounds for a given location manager.
* @scenario				Adds bounds for a given location manager\n
*						Deletes bounds for a given location manager.
* @apicovered			location_manager_add_boundary, location_manager_remove_boundary
* @passcase				When location_manager_add_boundary and location_manager_remove_boundary are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		It invokes location_manager_set_zone_changed_cb() when a boundary is entered or left, if you set a callback with location_manager_set_zone_changed_cb
* @remarks				Callback is not checked, as callback checking is manual
*/
int ITc_location_manager_add_remove_boundary_rect_p(void)
{
	START_TEST_MANAGER;

	//Add the rect bounds
	location_bounds_h bounds_rect = NULL;
	location_coords_s left_top;
	location_coords_s right_bottom;
	left_top.latitude = 30;
	left_top.longitude = 30;
	right_bottom.latitude = 10;
	right_bottom.longitude = 50;

	location_bound_error_e nRet1 = location_bounds_create_rect(left_top, right_bottom, &bounds_rect);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_create_rect", LocationBoundsGetError(nRet1));

	// Target API
	location_error_e nRet = location_manager_add_boundary(g_stManager, bounds_rect);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_add_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_rect));

	// Target API
	nRet = location_manager_remove_boundary(g_stManager, bounds_rect);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_remove_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_rect));

	nRet1 = location_bounds_destroy(bounds_rect);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_destroy", LocationBoundsGetError(nRet1));

	return 0;
}


//& purpose: Adds/Removes bounds for a given location manager.
//& type: auto

/**
* @testcase				ITc_location_manager_add_remove_boundary_polygon_p
* @since_tizen			2.3
* @author            	SRID(shobhit.v)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Adds/Removes bounds for a given location manager.
* @scenario				Adds bounds for a given location manager\n
*						Deletes bounds for a given location manager.
* @apicovered			location_manager_add_boundary, location_manager_remove_boundary
* @passcase				When location_manager_add_boundary and location_manager_remove_boundary are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		It invokes location_manager_set_zone_changed_cb() when a boundary is entered or left, if you set a callback with location_manager_set_zone_changed_cb
* @remarks				Callback is not checked, as callback checking is manual
*/
int ITc_location_manager_add_remove_boundary_polygon_p(void)
{
	START_TEST_MANAGER;

	//Add the polygon bounds
	location_bounds_h bounds_poly = NULL;

	int poly_size = 3;
	location_coords_s coord_list[poly_size];
	coord_list[0].latitude = 10;
	coord_list[0].longitude = 10;
	coord_list[1].latitude = 20;
	coord_list[1].longitude = 20;
	coord_list[2].latitude = 30;
	coord_list[2].longitude = 30;

	location_bound_error_e nRet1 = location_bounds_create_polygon(coord_list, poly_size, &bounds_poly);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_create_polygon", LocationBoundsGetError(nRet1));

	// Target API
	location_error_e nRet = location_manager_add_boundary(g_stManager, bounds_poly);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_add_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_poly));

	// Target API
	nRet = location_manager_remove_boundary(g_stManager, bounds_poly);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_remove_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_poly));

	nRet1 = location_bounds_destroy(bounds_poly);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_destroy", LocationBoundsGetError(nRet1));

	return 0;
}
//& purpose: Registers/Unregisters a callback function to be invoked periodically with updated position information
//& type: auto

/**
* @testcase				ITc_location_manager_set_unset_position_updated_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Registers/Unregisters a callback function to be invoked periodically with updated position information
* @scenario				Registers a callback function to be invoked periodically with updated position information\n
*						Unregisters the callback function
* @apicovered			location_manager_set_position_updated_cb, location_manager_unset_position_updated_cb
* @passcase				When location_manager_set_position_updated_cb and location_manager_unset_position_updated_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_position_updated_cb() will be invoked
*/
int ITc_location_manager_set_unset_position_updated_cb_p(void)
{
	START_TEST_MANAGER;

	g_bCallbackHit = false;

	// Target API
	location_error_e nRet = location_manager_set_position_updated_cb(g_stManager, LocationPositionUpdatedCB, 1, NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_position_updated_cb", LocationManagerGetError(nRet));

	// Target API
	nRet = location_manager_unset_position_updated_cb(g_stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_position_updated_cb", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked periodically with updated velocity information
//& type: auto

/**
* @testcase				ITc_location_manager_set_unset_velocity_updated_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Registers/Unregisters a callback function to be invoked periodically with updated velocity information
* @scenario				Registers a callback function to be invoked periodically with updated velocity information\n
*						Unregisters the callback function
* @apicovered			location_manager_set_velocity_updated_cb, location_manager_unset_velocity_updated_cb
* @passcase				When location_manager_set_velocity_updated_cb and location_manager_unset_velocity_updated_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_velocity_updated_cb() will be invoked
*/
int ITc_location_manager_set_unset_velocity_updated_cb(void)
{
	START_TEST_MANAGER;

	g_bCallbackHit = false;

	// Target API
	location_error_e nRet = location_manager_set_velocity_updated_cb(g_stManager, LocationVelocityUpdatedCB, 1, NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_velocity_updated_cb", LocationManagerGetError(nRet));

	// Target API
	nRet = location_manager_unset_velocity_updated_cb(g_stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_velocity_updated_cb", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked when the previously set boundary area is entered or left.
//& type: auto

/**
* @testcase				ITc_location_manager_set_unset_zone_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Registers/Unregisters a callback function to be invoked when the previously set boundary area is entered or left.
* @scenario				Registers a callback function to be invoked when the previously set boundary area is entered or left\n
*						Check if callback is invoked\n
*						Unregisters the callback function
* @apicovered			location_manager_set_zone_changed_cb, location_manager_unset_zone_changed_cb
* @passcase				When location_manager_set_zone_changed_cb and location_manager_unset_zone_changed_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_zone_changed_cb() will be invoked
* @remarks				Callback is not checked, as callback checking is manual
*/
int ITc_location_manager_set_unset_zone_changed_cb_p(void)
{
	START_TEST_MANAGER;

	// Target API
	location_error_e nRet = location_manager_set_zone_changed_cb(g_stManager, LocationZoneChangedCB, NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_zone_changed_cb", LocationManagerGetError(nRet));

	// Target API
	nRet = location_manager_unset_zone_changed_cb(g_stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_zone_changed_cb", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Retrieves all location bounds by invoking a specific callback for each location bounds
//& type: auto

/**
* @testcase				ITc_location_manager_foreach_boundary_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Retrieves all location bounds by invoking a specific callback for each location bounds
* @scenario				Add boundary\n
*						Retrieve all location bounds by invoking a specific callback for each location bounds\n
*						Remove boundary
* @apicovered			location_manager_foreach_boundary
* @passcase				When location_manager_foreach_boundary is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_bounds_cb() will be invoked
*/
int ITc_location_manager_foreach_boundary_p(void)
{
	START_TEST_MANAGER;

	//Add the circle bounds
	location_bounds_h bounds_circle;
	location_coords_s center;
	center.latitude = 37.258;
	center.longitude = 127.056;
	double radius = 30;
	int nTimeoutId = 0;

	location_bound_error_e nRet1 = location_bounds_create_circle(center, radius, &bounds_circle);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_create_circle", LocationBoundsGetError(nRet1));

	location_error_e nRet = location_manager_add_boundary(g_stManager, bounds_circle);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_add_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_circle));

	g_bCallbackHit = false;

	// Target API
	nRet = location_manager_foreach_boundary(g_stManager, LocationBoundsCB, NULL);
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_foreach_boundary", LocationManagerGetError(nRet), location_bounds_destroy(bounds_circle));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] Callback failed\\n", __LINE__, API_NAMESPACE);
		location_bounds_destroy(bounds_circle);
		return 1;
	}

	nRet1 = location_manager_remove_boundary(g_stManager, bounds_circle);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_manager_remove_boundary", LocationBoundsGetError(nRet1));

	nRet1 = location_bounds_destroy(bounds_circle);
	PRINT_RESULT(LOCATION_BOUNDS_ERROR_NONE, nRet1, "location_bounds_destroy", LocationBoundsGetError(nRet1));

	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked when the location setting is changed.
//& type: auto

/**
* @testcase				ITc_location_manager_set_unset_setting_changed_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Registers/Unregisters a callback function to be invoked when the location setting is changed.
* @scenario				Registers a callback function to be invoked when the location setting is changed\n
*						Unregisters the callback function
* @apicovered			location_manager_set_setting_changed_cb, location_manager_unset_setting_changed_cb
* @passcase				When location_manager_set_setting_changed_cb and location_manager_unset_setting_changed_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		location_setting_changed_cb() will be invoked
*/
int ITc_location_manager_set_unset_setting_changed_cb_p(void)
{
	START_TEST_MANAGER;

	location_method_e eTestLocationMethod = -1;
	location_method_e location_method[] = {
		LOCATIONS_METHOD_HYBRID,
		LOCATIONS_METHOD_GPS,
		LOCATIONS_METHOD_WPS,
		LOCATIONS_METHOD_PASSIVE,
	};

	int nEnumSize = sizeof(location_method) / sizeof(location_method[0]);
	int nEnumCounter = 0;
	for ( nEnumCounter=0; nEnumCounter < nEnumSize; nEnumCounter++ )
	{
		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_WPS )
		{
			if ( g_bIsLocationFeatureSupported && g_bIsWpsFeatureSupported)
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_GPS )
		{
			if ( g_bIsLocationFeatureSupported && g_bIsGpsFeatureSupported )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_HYBRID )
		{
			if ( g_bIsLocationFeatureSupported && ( g_bIsGpsFeatureSupported || g_bIsWpsFeatureSupported) )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}
		if ( location_method[nEnumCounter] == LOCATIONS_METHOD_PASSIVE )
		{
			if ( g_bIsLocationFeatureSupported )
			{
				eTestLocationMethod = location_method[nEnumCounter];
			}
		}

		if ( eTestLocationMethod >= LOCATIONS_METHOD_HYBRID )
		{
			g_bCallbackHit = false;

			if ( eTestLocationMethod < LOCATIONS_METHOD_PASSIVE ) {
				// Target API
				location_error_e nRet = location_manager_set_setting_changed_cb(location_method[nEnumCounter], LocationSettingChangedCB, NULL);
				PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_setting_changed_cb", LocationManagerGetError(nRet));

				// Target API
				nRet = location_manager_unset_setting_changed_cb(location_method[nEnumCounter]);
				PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_setting_changed_cb", LocationManagerGetError(nRet));
			}
			else
			{
				// Target API
				location_error_e nRet = location_manager_set_setting_changed_cb(location_method[nEnumCounter], LocationSettingChangedCB, NULL);
				PRINT_RESULT(LOCATIONS_ERROR_INCORRECT_METHOD, nRet, "location_manager_set_setting_changed_cb", LocationManagerGetError(nRet));

				// Target API
				nRet = location_manager_unset_setting_changed_cb(location_method[nEnumCounter]);
				PRINT_RESULT(LOCATIONS_ERROR_INCORRECT_METHOD, nRet, "location_manager_unset_setting_changed_cb", LocationManagerGetError(nRet));
			}
		}
	}

	return 0;
}

//& purpose: Request to update current location once.
//& type: auto

/**
* @testcase				ITc_location_manager_request_single_location_p
* @since_tizen			2.3
* @author				SRID(sameer.g1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Request to update current location once.
* @scenario				Create location manager\n
*						Request to update current location once\n
*						check callback\n
*						Destroy location manager
* @apicovered			location_manager_request_single_location
* @passcase				When location_manager_request_single_location is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			NA
* @postcondition		It invokes location_updated_cb()
*/
int ITc_location_manager_request_single_location_p(void)
{
	START_TEST_MANAGER;

	int nTimeoutId = 0;
	int nTimeout = 30;

	// Target API
	int nRet = location_manager_request_single_location(g_stManager, nTimeout, LocationUpdatedCB, NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_request_single_location", LocationManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if ( g_bCallbackHit != true || g_bCallbackReturnValue != true )
	{
		FPRINTF("[Line : %d][%s] Callback failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& purpose: Checks whether the given location method is enabled or not on setting.
//& type: auto

/**
* @testcase				ITc_location_manager_is_enabled_method_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type					auto
* @description			Checks whether the given location method is enabled or not on setting.
* @scenario				Create manager\n
*						Check whether the given location method is enabled or not\n
*						Destroy manager
* @apicovered			location_manager_is_enabled_method
* @passcase				When location_manager_is_enabled_method is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_manager_is_enabled_method_p(void)
{
	START_TEST_MANAGER;

	bool bEnable = false;

	// Target API
	location_error_e nRet = location_manager_is_enabled_method(LOCATIONS_METHOD_HYBRID, &bEnable);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_is_enabled_method", LocationManagerGetError(nRet));
	if ( bEnable == false )
	{
		FPRINTF("[Line : %d][%s] location_manager_is_enabled_method returned enable = %d\\n", __LINE__, API_NAMESPACE, bEnable);
		return 1;
	}
	return 0;
}

//& purpose: Registers/Unregisters a callback function to be invoked at defined interval with updated location information.
//& type: auto
/**
 * @testcase				ITc_location_manager_set_unset_location_changed_cb_p
 * @since_tizen				2.4
 * @author             		SRID(arjun.kumar)
 * @reviewer          		SRID(gupta.sanjay)
 * @type					auto
 * @description				Registers/unregistered a callback function to be invoked at defined interval with updated location information.
 * @scenario				Registers a callback function to be invoked at defined interval with updated location information. \n
 *							Unregisters the callback function
 * @apicovered				location_manager_set_location_changed_cb , location_manager_unset_location_changed_cb
 * @passcase				When location_manager_set_location_changed_cb and location_manager_unset_location_changed_cb are successful.
 * @failcase				If target api fails or any precondition api fails.
 * @precondition			None
 * @postcondition			location_changed_cb() will be invoked.
 */
int ITc_location_manager_set_unset_location_changed_cb_p(void)
{
	START_TEST_MANAGER;

	int nTimeout = 1;

	// Set location changed Target API
	location_error_e nRet = location_manager_set_location_changed_cb(g_stManager, LocationChangedCB, nTimeout, NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_location_changed_cb", LocationManagerGetError(nRet));

	// unset location changed Target API
	nRet = location_manager_unset_location_changed_cb(g_stManager);
    PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_location_changed_cb", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Registers/unregisters a callback function to be invoked at minimum interval or minimum distance with updated position information.
//& type: auto
/**
 * @testcase				ITc_location_manager_set_unset_distance_based_location_changed_cb_p
 * @since_tizen				2.4
 * @author             		SRID(arjun.kumar)
 * @reviewer          		SRID(gupta.sanjay)
 * @type					auto
 * @description				Registers/unregisters a callback function to be invoked at minimum interval or minimum distance with updated position information.
 * @scenario				Registers a callback function to be invoked at minimum interval or minimum distance with updated position information\n
 *							Unregisters the callback function
 * @apicovered				location_manager_set_distance_based_location_changed_cb , location_manager_unset_distance_based_location_changed_cb
 * @passcase				When location_manager_set_location_changed_cb and location_manager_unset_location_changed_cb are successful.
 * @failcase				If target api fails or any precondition api fails.
 * @precondition			None
 * @postcondition			location_changed_cb() will be invoked.
 */
int ITc_location_manager_set_unset_distance_based_location_changed_cb_p(void)
{
	START_TEST_MANAGER;

	int nInterval = 1;
	int nDistance = 1;

	// Set Distance based location changed Target API
	location_error_e nRet = location_manager_set_distance_based_location_changed_cb(g_stManager, LocationChangedCB, nInterval,nDistance,NULL);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_distance_based_location_changed_cb", LocationManagerGetError(nRet));

	// unset Distance based location changed Target API
	nRet = location_manager_unset_distance_based_location_changed_cb(g_stManager);
    PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_distance_based_location_changed_cb", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: enable the mock location when developer mode is enable
//& type: auto
/**
 * @testcase				ITc_location_manager_enable_mock_location_p
 * @since_tizen				3.0
 * @author             		SRID(nibha.sharma)
 * @reviewer          		SRID(parshant.v)
 * @type					auto
 * @description				enable the mock location when developer mode is enable
 * @scenario				enable the mock location when developer mode is enable
 * @apicovered				location_manager_enable_mock_location
 * @passcase				When location_manager_enable_mock_location is successful.
 * @failcase				If target api fails or any precondition api fails.
 * @precondition			None
 * @postcondition			None
 */
int ITc_location_manager_enable_mock_location_p(void)
{
	START_TEST_MANAGER;

	bool bIsEnable = false;

	//Target API
	int nRet = location_manager_enable_mock_location(bIsEnable);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_enable_mock_location", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Sets and clears a mock location for the given location method
//& type: auto
/**
 * @testcase				ITc_location_manager_set_clear_mock_location_p
 * @since_tizen				3.0
 * @author					SRID(nibha.sharma)
 * @reviewer				SRID(parshant.v)
 * @type					auto
 * @description				Sets and clears a mock location for the given location method
 * @scenario				Sets and clears a mock location for the given location method
 * @apicovered				location_manager_set_mock_location	and location_manager_clear_mock_location
 * @passcase				When location_manager_set_mock_location and location_manager_clear_mock_location are successful.
 * @failcase				If target api fails or any precondition api fails.
 * @precondition			enable mock location and create location manager for mock location
 * @postcondition			release the location manager
 */
int ITc_location_manager_set_clear_mock_location_p(void)
{
	START_TEST_MANAGER;

	bool bIsEnable = true;
	bool bIsDisable = false;
	const double nLatitude = 10.0;
	const double nLongitude = 10.0;
	const double nAltitude = 20.0;
	const double nSpeed = 30.0;
	const double nDirection = 40.0;
	const double nAccuracy = 50.0;

	int nRet = location_manager_enable_mock_location(bIsEnable);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_enable_mock_location", LocationManagerGetError(nRet));

	//Target API
	nRet = location_manager_set_mock_location(g_stManager, nLatitude, nLongitude, nAltitude, nSpeed, nDirection, nAccuracy);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_mock_location", LocationManagerGetError(nRet));

	//Target API
	nRet = location_manager_clear_mock_location(g_stManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_clear_mock_location", LocationManagerGetError(nRet));

	nRet = location_manager_enable_mock_location(bIsDisable);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_enable_mock_location", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Checks whether mock location is enabled or not
//& type: auto
/**
 * @testcase				ITc_location_manager_is_enabled_mock_location_p
 * @since_tizen				3.0
 * @author					SRID(nibha.sharma)
 * @reviewer				SRID(parshant.v)
 * @type					auto
 * @description				Checks whether mock location is enabled or not
 * @scenario				Checks whether mock location is enabled or not
 * @apicovered				location_manager_is_enabled_mock_location
 * @passcase				When location_manager_is_enabled_mock_location api is successful.
 * @failcase				If target api fails or any precondition api fails.
 * @precondition			enable mock location and create location manager for mock location
 * @postcondition			release the location manager
 */
int ITc_location_manager_is_enabled_mock_location_p(void)
{
	START_TEST_MANAGER;

	bool bEnable = false;

	// Target API
	location_error_e nRet = location_manager_is_enabled_mock_location(&bEnable);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_is_enabled_mock_location", LocationManagerGetError(nRet));
	FPRINTF("[Line : %d][%s] location_manager_is_enabled_mock_location returned enable = %d\\n", __LINE__, API_NAMESPACE, bEnable);

	return 0;
}

/**
* @testcase				ITc_location_manager_get_velocity_accuracy_p
* @since_tizen			6.0
* @author            	SRID(priya.kohli)
* @reviewer         	SRID(shobhit.v)
* @type					auto
* @description			Gets the current velocity accuracy information.
* @scenario				Gets the current velocity accuracy information.
* @apicovered			location_manager_get_velocity_accuracy
* @passcase				When location_manager_get_velocity_accuracy is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_manager_get_velocity_accuracy_p(void)
{
	START_TEST_MANAGER;

	double dVelocityAccuracy =  -1;

	location_error_e nRet = location_manager_get_velocity_accuracy(g_stManager, &dVelocityAccuracy);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_velocity_accuracy", LocationManagerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
