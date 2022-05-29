//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-geofence-manager-common.h"

/**
 * @function 		ITs_geofence_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_geofence_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Geofence_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	bool bFeatureSupported;
	g_bFeatureMismatch = g_bFeatureNotSupported = false;
	if ( !TCTCheckSystemInfoFeatureSupported(LOCATION_GEOFENCE_FEATURE, API_NAMESPACE) )
	{
		bFeatureSupported = false;
	}
	else
	{
		bFeatureSupported = true;
	}

	g_hGeofenceManager = NULL;
	int nRet = geofence_manager_create(&g_hGeofenceManager);
	FPRINTF("[Line : %d][%s] geofence_manager_create : return %d (%s)\\n", __LINE__, API_NAMESPACE, nRet, GeofenceManagerGetError(nRet));
	if( !bFeatureSupported )
	{
		if( nRet == GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED )
		{
			g_bFeatureNotSupported = true;
		}
		else
		{
			g_bFeatureMismatch = true;
		}
	}
	else
	{
		if ( nRet != GEOFENCE_MANAGER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] geofence_manager_create failed in startup, error returned = %s\\n", __LINE__, API_NAMESPACE, GeofenceManagerGetError(nRet));
			g_bIsGeofenceCreated = false;
		}
		else if(g_hGeofenceManager == NULL)
		{
			FPRINTF("[Line : %d][%s] geofence_manager_create failed in startup, output handle is NULL\\n", __LINE__, API_NAMESPACE);
			g_bIsGeofenceCreated = false;
		}
		else
		{
			g_bIsGeofenceCreated = true;
		}
	}

	return;
}

/**
 * @function 		ITs_geofence_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_geofence_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Geofence_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bIsGeofenceCreated )
	{
		int nRet = geofence_manager_destroy(g_hGeofenceManager);
		if ( nRet != GEOFENCE_MANAGER_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] geofence_manager_destroy failed in cleanup, error returned = %s\\n", __LINE__, API_NAMESPACE, GeofenceManagerGetError(nRet));
		}
	}
	
	return;
}

/** @addtogroup	itc-geofence-testcases
* @brief 		Integration testcases for module geofence
* @ingroup		itc-geofence
* @{
*/


//& purpose: get geofence type
//& type: auto
/**
 * @testcase 				ITc_geofence_get_type_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence type
 * @scenario				get geofence type
 * @apicovered				geofence_manager_add_place, geofence_create_bluetooth, geofence_manager_add_fence, geofence_get_type, geofence_manager_remove_fence, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_bluetooth, geofence_manager_add_fence, geofence_get_type is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_type_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "BT";
	char *pszPlaceName = "SOME_PLACE";
	geofence_type_e type;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_bluetooth(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_bluetooth", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_bluetooth");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_get_type(geofenceH, &type);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_type", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	if (type != GEOFENCE_TYPE_BT)
	{
		FPRINTF("[Line : %d][%s] type is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence place id
//& type: auto
/**
 * @testcase 				ITc_geofence_get_place_id_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence place id
 * @scenario				get geofence place id
 * @apicovered				geofence_manager_add_place, geofence_create_bluetooth, geofence_manager_add_fence, geofence_get_place_id, geofence_manager_remove_fence, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_bluetooth, geofence_manager_add_fence, geofence_get_place_id is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_place_id_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "BT";
	char *pszPlaceName = "SOME_PLACE";

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_bluetooth(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_bluetooth", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_bluetooth");
	
	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_get_place_id(geofenceH, &nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_place_id", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_INT(nPlaceId, "geofence_get_place_id");

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence latitude
//& type: auto
/**
 * @testcase 				ITc_geofence_get_latitude_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence latitude
 * @scenario				get geofence latitude
 * @apicovered				geofence_manager_add_place, geofence_create_geopoint, geofence_get_latitude, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_geopoint, geofence_get_latitude is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_latitude_p(void)
{
	START_TEST;
	
	int nPlaceId = 0;
	geofence_h geofenceH = NULL;
	char *pszAddress = "SOME_PLACE";
	char *pszPlaceName = "SOME_PLACE";
	double dLatitude = 1.2345, dLongitude = 2.3456;
	int nRadius = 100;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_geopoint(nPlaceId, dLatitude, dLongitude, nRadius, pszAddress, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_geopoint", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_geopoint");

	nRet = geofence_get_latitude(geofenceH, &dLatitude);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_latitude", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	if(dLatitude == 0.0)
	{
		FPRINTF("[Line : %d][%s] Latitude is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence longitude
//& type: auto
/**
 * @testcase 				ITc_geofence_get_longitude_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence longitude
 * @scenario				get geofence longitude
 * @apicovered				geofence_manager_add_place, geofence_create_geopoint, geofence_get_longitude, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_geopoint, geofence_get_longitude is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_longitude_p(void)
{
	START_TEST;
	
	int nPlaceId = 0;
	geofence_h geofenceH = NULL;
	char *pszAddress = "SOME_PLACE";
	char *pszPlaceName = "SOME_PLACE";
	double dLatitude = 1.2345, dLongitude = 2.3456;
	int nRadius = 100;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_geopoint(nPlaceId, dLatitude, dLongitude, nRadius, pszAddress, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_geopoint", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_geopoint");

	nRet = geofence_get_longitude(geofenceH, &dLongitude);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_longitude", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	if(dLongitude == 0.0)
	{
		FPRINTF("[Line : %d][%s] Longitude is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence radius
//& type: auto
/**
 * @testcase 				ITc_geofence_get_radius_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence radius
 * @scenario				get geofence radius
 * @apicovered				geofence_manager_add_place, geofence_create_geopoint, geofence_get_radius, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_geopoint, geofence_get_radius is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_radius_p(void)
{
	START_TEST;
	
	int nPlaceId = 0;
	geofence_h geofenceH = NULL;
	char *pszAddress = "SOME_PLACE";
	char *pszPlaceName = "SOME_PLACE";
	double dLatitude = 1.2345, dLongitude = 2.3456;
	int nRadius = 100;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_geopoint(nPlaceId, dLatitude, dLongitude, nRadius, pszAddress, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_geopoint", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_geopoint");

	nRet = geofence_get_radius(geofenceH, &nRadius);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_radius", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_INT(nRadius, "geofence_get_radius");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence bssid
//& type: auto
/**
 * @testcase 				ITc_geofence_get_bssid_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence bssid
 * @scenario				get geofence bssid
 * @apicovered				geofence_manager_add_place, geofence_create_bluetooth, geofence_get_bssid, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_bluetooth, geofence_get_bssid is successful
 * @failcase				If target API or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_bssid_p(void)
{
	START_TEST;
	
	geofence_h geofenceH = NULL;
	char *pszBSSID = "88:30:8A:6C:28:16";
	char *pszSSID = "BT";
	char *pszPlaceName = "SOME_PLACE";
	char *pszGetBSSID = NULL;
	int nPlaceId = 0;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_bluetooth(nPlaceId, pszBSSID, pszSSID, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_bluetooth", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_bluetooth");

	nRet = geofence_get_bssid(geofenceH, &pszGetBSSID);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_bssid", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_STRING(pszGetBSSID, "geofence_get_bssid");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: get geofence ssid
//& type: auto
/**
 * @testcase 				ITc_geofence_get_ssid_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence ssid
 * @scenario				get geofence ssid
 * @apicovered				geofence_manager_add_place, geofence_create_bluetooth, geofence_get_ssid, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_bluetooth, geofence_get_ssid is successful
 * @failcase				If target API any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_ssid_p(void)
{
	START_TEST;
	
	geofence_h geofenceH = NULL;
	char *pszBSSID = "88:30:8A:6C:28:16";
	char *pszSSID = "BT";
	char *pszPlaceName = "SOME_PLACE";
	char *pszGetSSID = NULL;
	int nPlaceId = 0;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_bluetooth(nPlaceId, pszBSSID, pszSSID, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_bluetooth", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_bluetooth");

	nRet = geofence_get_ssid(geofenceH, &pszGetSSID);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_ssid", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_STRING(pszGetSSID, "geofence_get_ssid");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}


//& purpose: get geofence address
//& type: auto
/**
 * @testcase 				ITc_geofence_get_address_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				get geofence address
 * @scenario				get geofence address
 * @apicovered				geofence_manager_add_place, geofence_create_geopoint, geofence_get_address, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_geopoint, geofence_get_address is successful
 * @failcase				If target API or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_get_address_p(void)
{
	START_TEST;

	geofence_h geofenceH = NULL;
	char *pszAddress = "SOME_PLACE";
	char *pszPlaceName = "SOME_PLACE";
	char *pszGetAddress = NULL;
	int nPlaceId = 0;
	double dLatitude = 1.2345, dLongitude = 2.3456;
	int nRadius = 100;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_geopoint(nPlaceId, dLatitude, dLongitude, nRadius, pszAddress, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_geopoint", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_geopoint");

	nRet = geofence_get_address(geofenceH, &pszGetAddress);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_get_address", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_STRING(pszGetAddress, "geofence_get_address");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}
 
//& purpose: create geopoint
//& type: auto
/**
 * @testcase 				ITc_geofence_create_geopoint_desroy_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create geopoint
 * @scenario				geofence_get_place_id\n
 *							geofence_get_latitude\n
 *							geofence_get_longitude\n
 *							geofence_get_radius\n
 *							create geopoint
 * @apicovered				geofence_manager_add_place, geofence_create_geopoint, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_geopoint, geofence_destroy is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_create_geopoint_desroy_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nRadius = 100;
	double dLatitude = 1.2345, dLongitude = 2.3456;
	geofence_h geofenceH = NULL;
	const char *pAddress = "SOME_PLACE";
	char *pszPlaceName = "SOME_PLACE";

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");
	
	nRet = geofence_create_geopoint(nPlaceId, dLatitude, dLongitude, nRadius, pAddress, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_geopoint", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_geopoint");
	
	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: create bluetooth geopoint
//& type: auto
/**
 * @testcase 				ITc_geofence_create_bluetooth_destroy_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create bluetooth geopoint
 * @scenario				geofence_get_place_id\n
 *							get geofence bssid\n
 *							create bluetooth geopoint
 * @apicovered				geofence_manager_add_place, geofence_create_bluetooth, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_bluetooth, geofence_destroy is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_create_bluetooth_destroy_p(void)
{
	START_TEST;
	
	int nPlaceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "BT";
	char *pszPlaceName = "SOME_PLACE";

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_bluetooth(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_bluetooth", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_bluetooth");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: create bluetooth wifi
//& type: auto
/**
 * @testcase 				ITc_geofence_create_wifi_destroy_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create wifi
 * @scenario				geofence_get_place_id\n
 *							get geofence bssid\n
 *							create bluetooth wifi
 * @apicovered				geofence_manager_add_place, geofence_create_wifi, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_wifi, geofence_destroy is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_create_wifi_destroy_p(void)
{
	START_TEST;
	
	int nPlaceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: create/destroy geofence status
//& type: auto
/**
 * @testcase 				ITc_geofence_status_create_destroy_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create/destroy geofence status
 * @scenario				Set unset geofence event callback\n
 *							create/destroy geofence status
 * @apicovered				geofence_manager_add_place, geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_destroy, geofence_destroy, geofence_manager_remove_fence, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_destroy is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_status_create_destroy_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";
	geofence_status_h geofenceStatusH = NULL;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_status_create(nFenceId, &geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_create", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	CHECK_HANDLE(geofenceStatusH, "geofence_status_create");
	
	nRet = geofence_status_destroy(geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: geofence status get state
//& type: auto
/**
 * @testcase 				ITc_geofence_status_get_state_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				geofence status get state
 * @scenario				Set unset geofence event callback\n
 *							create/destroy geofence status\n
 *							geofence status get state
 * @apicovered				geofence_manager_add_place, geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_get_state, geofence_status_destroy, geofence_manager_remove_fence, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_get_state is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_status_get_state_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";
	geofence_status_h geofenceStatusH = NULL;
	geofence_state_e eGeofenceState = -1;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_status_create(nFenceId, &geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_create", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	CHECK_HANDLE(geofenceStatusH, "geofence_status_create");

	nRet = geofence_status_get_state(geofenceStatusH, &eGeofenceState);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_get_state", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	if((eGeofenceState<0) || (eGeofenceState>2))
	{
		FPRINTF("[Line : %d][%s] state is not valid\\n", __LINE__, API_NAMESPACE);
		geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
		geofence_destroy(geofenceH);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}

	nRet = geofence_status_destroy(geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: geofence status get duration
//& type: auto
/**
 * @testcase 				ITc_geofence_status_get_duration_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				geofence status get duration
 * @scenario				Set unset geofence event callback\n
 *							create/destroy geofence status\n
 *							geofence status get duration
 * @apicovered				geofence_manager_add_place. geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_get_duration, geofence_status_destroy, geofence_manager_remove_fence, geofence_destroy, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_create_wifi, geofence_manager_add_fence, geofence_status_create, geofence_status_get_duration is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_status_get_duration_p(void)
{
	START_TEST;

	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";
	geofence_status_h geofenceStatusH = NULL;
	int nDuration = -1;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_status_create(nFenceId, &geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_create", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	CHECK_HANDLE(geofenceStatusH, "geofence_status_create");

	nRet = geofence_status_get_duration(geofenceStatusH, &nDuration);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_get_duration", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_status_destroy(geofenceStatusH);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	if (nDuration == -1){
		FPRINTF("[Line : %d][%s] nDuration is not valid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = geofence_status_destroy(geofenceStatusH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_status_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

/** @} */ //end of itc-geofence
/** @} */ //end of itc-geofence-testcases
