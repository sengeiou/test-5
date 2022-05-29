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

location_manager_h g_hLocationManager = NULL;
location_method_e g_eMethodType = LOCATIONS_METHOD_GPS;

/**
* @function 		ITs_location_gps_status_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_location_gps_status_startup(void)
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
	g_bIsGpsFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_GPS_FEATURE, API_NAMESPACE);
	g_bIsLocationFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_FEATURE, API_NAMESPACE);

	g_bIsLocationManagerSupported = g_bIsLocationFeatureSupported && g_bIsGpsFeatureSupported;
	g_bLocationMismatch = false;
	g_bLocationNotSupported = false;
	LocationManagerCreateStartMethod(&g_hLocationManager, g_eMethodType);
	g_bIsGPSSatelliteSupported = false;
	g_bIsGPSSatelliteSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_GPS_SATELLITE, API_NAMESPACE);
}

/**
* @function 		ITs_location_gps_status_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_location_gps_status_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bCleanupNotRequired != true )
	{
		LocationManagerStopDestroyMethod(&g_hLocationManager);
	}
	return;
}

/**
* @function 		LocationGpsStatusGetSatellitesCB
* @description	 	captured satellite information
* @parameter		int, int, int, int, bool, void *user_data
* @return 			bool
*/
bool LocationGpsStatusGetSatellitesCB(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use, void *user_data)
{
	FPRINTF("[Line : %d][%s]Invoked LocationGpsStatusGetSatellitesCB\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s][Current Satellite information] azimuth : %d, elevation : %d, prn :%d, snr : %d, used: %d\\n", __LINE__, API_NAMESPACE, azimuth, elevation, prn, snr, is_in_use);
	return true;
}

/**
* @function 		LocationGpsStatusLastSatellitesForeachCB
* @description	 	captured last satellites information
* @parameter		int, int, int, int, bool, void *user_data
* @return 			bool
*/
bool LocationGpsStatusLastSatellitesForeachCB(unsigned int azimuth, unsigned int elevation, unsigned int prn, int snr, bool is_in_use, void *user_data)
{
	FPRINTF("[Line : %d][%s]Invoked LocationGpsStatusLastSatellitesForeachCB\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s][Last Satellite information] azimuth : %d, elevation : %d, prn :%d, snr : %d, used: %d\\n", __LINE__, API_NAMESPACE, azimuth, elevation, prn, snr, is_in_use);
	return true;
}

/**
* @function 		LocationGpsStatusSatelliteUpdatedCB
* @description	 	captured updated information of satellites in certain duration
* @parameter		int, int, int, int, bool, void *user_data
* @return 			bool
*/
void LocationGpsStatusSatelliteUpdatedCB(int num_of_active, int num_of_inview,  time_t timestamp, void *user_data)
{
	g_bCallbackHit = true;
	FPRINTF("[Line : %d][%s]Invoked LocationGpsStatusSatelliteUpdatedCB\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s][Last Satellite information] num_of_active : %d, num_of_inview : %d, timestamp :%ld\\n", __LINE__, API_NAMESPACE, num_of_active, num_of_inview, timestamp);
	g_bIsSatelliteEnabled = true;
	if ( (g_pLocationManagerMainLoop != NULL) && (g_bIsServiceEnabled == true) )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}
	return;
}



/** @addtogroup itc-location-gps-testcases
*  @brief 		Integration testcases for module location-gps
*  @ingroup 	itc-location-gps
*  @{
*/


//& purpose: To check GPS NMEA data
//& type: auto
/**
* @testcase 			ITc_gps_status_get_nmea_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check GPS NMEA data
* @scenario				Get the GPS NMEA data\n
* 						Check data for null
* @apicovered			gps_status_get_nmea
* @passcase				When gps_status_get_nmea is successful
* @failcase				If target API gps_status_get_nmea fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_get_nmea_p(void)
{
	START_TEST_GPS;
	int nRet = -1;
	char *pszNMEA = NULL;

	nRet = gps_status_get_nmea(g_hLocationManager, &pszNMEA);
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_get_nmea() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_get_nmea", LocationManagerGetError(nRet));

	if ( pszNMEA == NULL )
	{
		FPRINTF("[Line : %d][%s] gps_status_get_nmea failed, NMEA data is null\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	free(pszNMEA);
	pszNMEA = NULL;

	return 0;
}


//& purpose: To check the information of satellites
//& type: auto
/**
* @testcase 			ITc_gps_status_get_satellite_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the information of satellites
* @scenario				Get the information of satellites\n
* 						Verify the information
* @apicovered			gps_status_get_satellite
* @passcase				When gps_status_get_satellite is successful
* @failcase				If target API  fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_get_satellite_p(void)
{
	START_TEST_GPS;

	int nGetActive = -1;
	int nGetInView = -1;
	time_t tGetTimestamp = 0;
	location_method_e method;

	location_error_e nRet = location_manager_get_method(g_hLocationManager, &method);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_method", LocationManagerGetError(nRet));
	PRINT_RESULT(LOCATIONS_METHOD_GPS, method, "location_manager_get_method", LocationManagerGetError(nRet));

	nRet = gps_status_get_satellite(g_hLocationManager, &nGetActive, &nGetInView, &tGetTimestamp);// Target API
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_get_satellite() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_get_satellite", LocationManagerGetError(nRet));

	if ( (nGetActive == -1) || (nGetInView == -1) || (tGetTimestamp == 0) )
	{
		FPRINTF("[Line : %d][%s] gps_status_get_satellite failed, return invalid values\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line : %d][%s] gps_status_get_satellite active :%d, in_view : %d, time_stamp : %ld\\n", __LINE__, API_NAMESPACE, nGetActive, nGetInView, tGetTimestamp);
		return 1;
	}

	return 0;
}

//& purpose: To check the last information of satellites
//& type: auto
/**
* @testcase 			ITc_gps_status_get_last_satellite_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the last information of satellites
* @scenario				Get the last information of satellites\n
* 						Verify the information
* @apicovered			gps_status_get_last_satellite
* @passcase				When gps_status_get_last_satellite is successful
* @failcase				If target API  fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_get_last_satellite_p(void)
{
	START_TEST_GPS;

	int nGetActive = -1;
	int nGetInView = -1;
	time_t tGetTimestamp = 0;
	location_method_e method;

	location_error_e nRet = location_manager_get_method(g_hLocationManager, &method);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_method", LocationManagerGetError(nRet));
	PRINT_RESULT(LOCATIONS_METHOD_GPS, method, "location_manager_get_method", LocationManagerGetError(nRet));

	nRet = gps_status_get_last_satellite(g_hLocationManager, &nGetActive, &nGetInView, &tGetTimestamp);// Target API
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_get_last_satellite() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_get_last_satellite", LocationManagerGetError(nRet));

	if ( (nGetActive == -1) || (nGetInView == -1) || (tGetTimestamp == 0) )
	{
		FPRINTF("[Line : %d][%s] gps_status_get_last_satellite failed, return invalid values\\n", __LINE__, API_NAMESPACE);
		FPRINTF("[Line : %d][%s] gps_status_get_last_satellite active :%d, in_view : %d, time_stamp : %ld\\n", __LINE__, API_NAMESPACE, nGetActive, nGetInView, tGetTimestamp);
		return 1;
	}
	return 0;
}

//& purpose: To register the callback function for each last satellite which is recorded
//& type: auto
/**
* @testcase 			ITc_gps_status_foreach_last_satellites_in_view_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check the last information of satellites
* @scenario				Register the callback function for each last satellite which is recorded\n
* 						Verify the output of function
* @apicovered			gps_status_foreach_last_satellites_in_view
* @passcase				When gps_status_foreach_last_satellites_in_view is successful
* @failcase				If target API  fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_foreach_last_satellites_in_view_p(void)
{
	START_TEST_GPS;

	location_method_e method;
	location_error_e nRet = location_manager_get_method(g_hLocationManager, &method);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_method", LocationManagerGetError(nRet));
	PRINT_RESULT(LOCATIONS_METHOD_GPS, method, "location_manager_get_method", LocationManagerGetError(nRet));

	nRet = gps_status_foreach_last_satellites_in_view(g_hLocationManager, LocationGpsStatusLastSatellitesForeachCB, NULL);// Target API
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_foreach_last_satellites_in_view() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_foreach_last_satellites_in_view", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: To register callback function for each present satellite
//& type: auto
/**
* @testcase 			ITc_gps_status_foreach_satellites_in_view_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To register callback function for each present satellite
* @scenario				Register the callback function for each present satellite\n
* 						Verify the output of function
* @apicovered			gps_status_foreach_satellites_in_view
* @passcase				When gps_status_foreach_satellites_in_view is successful
* @failcase				If target API  fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_foreach_satellites_in_view_p(void)
{
	START_TEST_GPS;

	location_method_e method;
	location_error_e nRet = location_manager_get_method(g_hLocationManager, &method);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_get_method", LocationManagerGetError(nRet));
	PRINT_RESULT(LOCATIONS_METHOD_GPS, method, "location_manager_get_method", LocationManagerGetError(nRet));

	nRet = gps_status_foreach_satellites_in_view(g_hLocationManager, LocationGpsStatusGetSatellitesCB, NULL);// Target API
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_foreach_satellites_in_view() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_foreach_satellites_in_view", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: To register/unregister a callback function to be invoked at defined interval with updated satellite information
//& type: auto
/**
* @testcase 			ITc_gps_status_set_unset_satellite_updated_cb_p
* @since_tizen			2.3
* @author            	SRID(sameer.g1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			To check creates/destroy a rect type of new location bounds
* @scenario				register/unregister a callback function to be invoked at defined interval with updated satellite information\n
* 						unregister a callback function to be invoked at defined interval with updated satellite information
* @apicovered			gps_status_set_satellite_updated_cb, gps_status_unset_satellite_updated_cb
* @passcase				When gps_status_set_satellite_updated_cb and gps_status_unset_satellite_updated_cb are successful
* @failcase				If target APIs fails
* @precondition			location service with gps method should be start
* @postcondition		location service should be stop and location manager should be release
*/
int ITc_gps_status_set_unset_satellite_updated_cb_p(void)
{
	START_TEST_GPS;

	int nInterval = 1;
	int nRet = gps_status_set_satellite_updated_cb(g_hLocationManager, LocationGpsStatusSatelliteUpdatedCB, nInterval,  NULL);// Target API
	if ( false == g_bIsGPSSatelliteSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by gps_status_set_satellite_updated_cb() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_set_satellite_updated_cb", LocationManagerGetError(nRet));

	nRet = gps_status_unset_satellite_updated_cb(g_hLocationManager);// Target API
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "gps_status_unset_satellite_updated_cb", LocationManagerGetError(nRet));

	return 0;
}
/** @} */
/** @} */
