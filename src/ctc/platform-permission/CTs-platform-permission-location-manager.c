#include "CTs-platform-permission-common.h"
#include <locations.h>
#define FEATURE_LOCATION				"http://tizen.org/feature/location"
#define FEATURE_LOCATION_GPS			"http://tizen.org/feature/location.gps"
#define FEATURE_LOCATION_WPS			"http://tizen.org/feature/location.wps"
#define FEATURE_LOCATION_GPS_SATELITE	"http://tizen.org/feature/location.gps.satellite"
/**
* @function 		LocationManagerGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* LocationManagerGetError(location_error_e nRet)
{
	char *szErrorVal = "Unknown Error";
	switch ( nRet )
	{
	case LOCATIONS_ERROR_NONE:							szErrorVal = "LOCATIONS_ERROR_NONE";							break;
	case LOCATIONS_ERROR_OUT_OF_MEMORY:					szErrorVal = "LOCATIONS_ERROR_OUT_OF_MEMORY";					break;
	case LOCATIONS_ERROR_INVALID_PARAMETER:				szErrorVal = "LOCATIONS_ERROR_INVALID_PARAMETER";				break;
	case LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED:		szErrorVal = "LOCATIONS_ERROR_ACCESSIBILITY_NOT_ALLOWED";		break;
	case LOCATIONS_ERROR_NOT_SUPPORTED:					szErrorVal = "LOCATIONS_ERROR_NOT_SUPPORTED";					break;
	case LOCATIONS_ERROR_INCORRECT_METHOD:				szErrorVal = "LOCATIONS_ERROR_INCORRECT_METHOD";				break;
	case LOCATIONS_ERROR_NETWORK_FAILED:				szErrorVal = "LOCATIONS_ERROR_NETWORK_FAILED";					break;
	case LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE:			szErrorVal = "LOCATIONS_ERROR_SERVICE_NOT_AVAILABLE";			break;
	case LOCATIONS_ERROR_GPS_SETTING_OFF:				szErrorVal = "LOCATIONS_ERROR_GPS_SETTING_OFF";					break;
	case LOCATIONS_ERROR_SECURITY_RESTRICTED:			szErrorVal = "LOCATIONS_ERROR_SECURITY_RESTRICTED";				break;
	}

	return szErrorVal;

}

/**
* @function 		LocationGpsStatusSatelliteUpdatedCB
* @description	 	captured updated information of satellites in certain duration
* @parameter		int, int, int, int, bool, void *user_data
* @return 			bool
*/
void LocationGpsStatusSatelliteUpdatedCB(int num_of_active, int num_of_inview,  time_t timestamp, void *user_data)
{

	FPRINTF("[Line : %d][%s]Invoked LocationGpsStatusSatelliteUpdatedCB\\n", __LINE__, API_NAMESPACE);
	return;
}

#ifdef WEARABLE 	//Starts WEARABLE
/**
 * @function 		LocationUpdatedCB
 * @description	 	Called at defined interval with updated location information
 * @parameter		location_error_e error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double direction, double climb, void *user_data
 * @return 			NA
 */
static void LocationUpdatedCB(location_error_e error, double latitude, double longitude, double altitude, time_t timestamp, double speed, double direction, double climb, void *user_data)
{
	return;
}
#endif  //End WEARABLE

/**
* @function 		CTs_platform_permission_locationmanager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_locationmanager_startup(void)
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
* @function 		CTs_platform_permission_locationmanager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_locationmanager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& purpose: Checking http://tizen.org/privilege/location privilege
//& type: auto
/**
* @testcase			CTc_Location_PrivilegeLocation_start
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create location manager\n
* 					Start location manager\n
*					Get location\n
*					Destroy location manager
* @apicovered		location_manager_create, location_manager_start, location_manager_stop, location_manager_get_location and location_manager_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/

int CTc_Location_PrivilegeLocation_start(void)
{
	START_TEST;
	bool bIsLocationFeatureSupported = false;
	bool bIsLocationGpsFeatureSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, bIsLocationFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS, bIsLocationGpsFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsLocationFeatureSupported ) || ( bIsLocationGpsFeatureSupported == false) )
		{
			FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
			return 0;
		}

	location_method_e eLocationMethod = LOCATIONS_METHOD_HYBRID;
	location_manager_h hLocationManager = NULL;


	int nRet = location_manager_create(eLocationMethod, &hLocationManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));

	nRet = location_manager_start(hLocationManager);
	if(nRet ==LOCATIONS_ERROR_NONE)
	{
	location_manager_stop(hLocationManager);
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "location_manager_start", LocationManagerGetError(nRet), location_manager_destroy(hLocationManager));

	location_manager_destroy(hLocationManager);
	return 0;
}
//& purpose: Checking http://tizen.org/privilege/location privilege
//& type: auto
/**
* @testcase			CTc_Location_PrivilegeLocation_set_satelite
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create location manager\n
* 					Start location manager\n
*					Get location\n
*					Destroy location manager
* @apicovered		location_manager_create, gps_status_set_satellite_updated_cb and location_manager_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/
int CTc_Location_PrivilegeLocation_set_satelite_updated_cb(void)
{
	START_TEST;
	int nInterval = 1;
	bool bIsLocationFeatureSupported = false;
	bool bIsLocationGpsFeatureSupported = false;

	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, bIsLocationFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS_SATELITE, bIsLocationGpsFeatureSupported, API_NAMESPACE);

	if (( false == bIsLocationFeatureSupported ) || ( bIsLocationGpsFeatureSupported == false))
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	location_method_e eLocationMethod = LOCATIONS_METHOD_HYBRID;
	location_manager_h hLocationManager = NULL;

	int nRet = location_manager_create(eLocationMethod, &hLocationManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));


	nRet = gps_status_set_satellite_updated_cb(hLocationManager, LocationGpsStatusSatelliteUpdatedCB, nInterval,  NULL);// Target API
	if(nRet ==LOCATIONS_ERROR_NONE)
	{
	gps_status_unset_satellite_updated_cb(hLocationManager);
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "gps_status_set_satellite_updated_cb", LocationManagerGetError(nRet), location_manager_destroy(hLocationManager));

	location_manager_destroy(hLocationManager);
	return 0;
}

//& purpose: Sets and clears a mock location for the given location method
//& type: auto
/**
 * @testcase 			CTc_Location_PrivilegeLocation_enable_mock_location
 * @since_tizen			3.0
 * @author             	SRID(arvin.mittal)
 * @reviewer          	SRID(shobhit.v)
 * @type 				auto
 * @description			enable the mock location when developer mode is enable
 * @scenario			enable the mock location when developer mode is enable
 * @apicovered			location_manager_enable_mock_location
 * @passcase			When location_manager_enable_mock_location is successful.
 * @failcase			If target api fails or any precondition api fails.
 * @precondition		NA
 * @postcondition		NA
 */
int CTc_Location_PrivilegeLocation_enable_mock_location(void)
{
	START_TEST;

	bool bIsLocationFeatureSupported = false;
	bool bIsLocationGpsFeatureSupported = false;
	bool bIsLocationWpsFeatureSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, bIsLocationFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS, bIsLocationGpsFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_WPS, bIsLocationWpsFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsLocationFeatureSupported ) || ( bIsLocationGpsFeatureSupported == false) || ( bIsLocationWpsFeatureSupported == false))
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	bool bIsEnable = false;

	int nRet = location_manager_enable_mock_location(bIsEnable);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "location_manager_enable_mock_location", LocationManagerGetError(nRet));

	return 0;
}

//& purpose: Sets a mock location for the given location method
//& type: auto
/**
 * @testcase 			CTc_Location_PrivilegeLocation_set_mock_location
 * @since_tizen			3.0
 * @author             	SRID(arvin.mittal)
 * @reviewer          	SRID(shobhit.v)
 * @type 				auto 
 * @description			set mock location 
 * @scenario			set mock location 
 * @apicovered			location_manager_set_mock_location				
 * @passcase			When location_manager_set_mock_location is successful.
 * @failcase			If target api fails or any precondition api fails.
 * @precondition		NA
 * @postcondition		NA
 */
int CTc_Location_PrivilegeLocation_set_mock_location(void)
{
	START_TEST;
	
	const double nLatitude = 10.0;
	const double nLongitude = 10.0;
	const double nAltitude = 20.0;
	const double nSpeed = 30.0;
	const double nDirection = 40.0;
	const double nAccuracy = 50.0;
	
	bool bIsLocationFeatureSupported = false;
	bool bIsLocationGpsFeatureSupported = false;
	bool bIsLocationWpsFeatureSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, bIsLocationFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS, bIsLocationGpsFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_WPS, bIsLocationWpsFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsLocationFeatureSupported ) || ( bIsLocationGpsFeatureSupported == false) || ( bIsLocationWpsFeatureSupported == false))
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	location_method_e eLocationMethod = LOCATIONS_METHOD_GPS;
	location_manager_h hLocationManager = NULL;
	int nRet = location_manager_create(eLocationMethod, &hLocationManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
			
	//Target API
	nRet = location_manager_set_mock_location(hLocationManager, nLatitude, nLongitude, nAltitude, nSpeed, nDirection, nAccuracy);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "location_manager_set_mock_location", LocationManagerGetError(nRet), location_manager_destroy(hLocationManager));
	location_manager_destroy(hLocationManager);
	
	return 0;
}

//& purpose: clears a mock location for the given location method
//& type: auto
/**
 * @testcase 			CTc_Location_PrivilegeLocation_clear_mock_location
 * @since_tizen			3.0
 * @author             	SRID(arvin.mittal)
 * @reviewer          	SRID(shobhit.v)
 * @type 				auto 
 * @description			clear mock location 
 * @scenario			clear mock location 
 * @apicovered			location_manager_clear_mock_location				
 * @passcase			When location_manager_set_mock_location is successful.
 * @failcase			If target api fails or any precondition api fails.
 * @precondition		NA
 * @postcondition		NA
 */
int CTc_Location_PrivilegeLocation_clear_mock_location(void)
{
	START_TEST;
	
	bool bIsLocationFeatureSupported = false;
	bool bIsLocationGpsFeatureSupported = false;
	bool bIsLocationWpsFeatureSupported = false;
	
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, bIsLocationFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS, bIsLocationGpsFeatureSupported, API_NAMESPACE);
	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_WPS, bIsLocationWpsFeatureSupported, API_NAMESPACE);
	if ( ( false == bIsLocationFeatureSupported ) || ( bIsLocationGpsFeatureSupported == false) || ( bIsLocationWpsFeatureSupported == false))
	{
		FPRINTF("[Line : %d][%s] Feature is not supported\\n", __LINE__, API_NAMESPACE);
		return 0;
	}
	
	location_method_e eLocationMethod = LOCATIONS_METHOD_GPS;
	location_manager_h hLocationManager = NULL;
	int nRet = location_manager_create(eLocationMethod, &hLocationManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));	

	nRet = location_manager_clear_mock_location(hLocationManager);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "location_manager_clear_mock_location", LocationManagerGetError(nRet), location_manager_destroy(hLocationManager));
	location_manager_destroy(hLocationManager);
	
	return 0;
}

#ifdef WEARABLE 	//Starts WEARABLE
//& purpose: Checking http://tizen.org/privilege/location privilege
//& type: auto
/**
* @testcase			CTc_Location_PrivilegeLocation_location_manager_request_single_location
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Request to update current location once.
* @apicovered		location_manager_create, location_manager_start, location_manager_stop, location_manager_get_location and location_manager_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition API returns non error value
* @precondition		NA
* @postcondition	NA
*/

int CTc_Location_PrivilegeLocation_location_manager_request_single_location(void)
{
	START_TEST;

	bool g_bIsSupported =false;
	int nTimeout = 1;

	IS_FEATURE_SUPPORTED(FEATURE_LOCATION, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_LOCATION);
		return 0;
	}

	bool g_bIsgpsSupported =false;

	IS_FEATURE_SUPPORTED(FEATURE_LOCATION_GPS, g_bIsgpsSupported, API_NAMESPACE);
	if ( !g_bIsgpsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_LOCATION_GPS);
		return 0;
	}

	location_method_e eLocationMethod = LOCATIONS_METHOD_HYBRID;
	location_manager_h hLocationManager = NULL;

	int nRet = location_manager_create(eLocationMethod, &hLocationManager);
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));

	nRet = location_manager_request_single_location ( hLocationManager, nTimeout, LocationUpdatedCB, NULL);
	if(nRet == LOCATIONS_ERROR_NONE)
	{
		location_manager_destroy(hLocationManager);
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "location_manager_request_single_location", LocationManagerGetError(nRet), location_manager_destroy(hLocationManager));

	location_manager_destroy(hLocationManager);

	return 0;
}
#endif  //End WEARABLE
