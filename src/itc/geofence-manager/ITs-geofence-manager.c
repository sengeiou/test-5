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

/** @addtogroup itc-geofence-manager
* @ingroup		itc
* @{
*/

/**
 * @function 		GeofenceProximityStateChangedCB
 * @description	 	Called for geofence state change
 * @parameter		int geofence_id, geofence_proximity_state_e state, geofence_proximity_provider_e provider, void *user_data
 * @return 			boolean value 
 */
void GeofenceProximityStateChangedCB(int geofence_id, geofence_proximity_state_e state, geofence_proximity_provider_e provider, void *user_data)
{
	g_bGeofencemanagerCBFlag = true;
	if(geofence_id < 0)
	{
		FPRINTF("[Line : %d][%s] geofence_id is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if((state<GEOFENCE_PROXIMITY_STATE_UNCERTAIN)||(state>GEOFENCE_PROXIMITY_STATE_IMMEDIATE))
	{
		FPRINTF("[Line : %d][%s] state is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else
	{
		g_bGeofencemanagerCBParameter = true;
	}
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}

/**
 * @function 		GeofenceManagerPlaceCB
 * @description	 	Called for geo place event
 * @parameter		place_id : The place id;place_name ;place_index;place_cnt;user_data : The user data passed from the foreach function
 * @return 			boolean value 
 */
bool GeofenceManagerPlaceCB(int place_id, const char *place_name, int place_index, int place_cnt, void *user_data)
{
	g_bGeofencemanagerCBFlag = true;
	if ( place_name == NULL )
	{
		FPRINTF("[Line : %d][%s] place_name is NULL\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(place_id < 0)
	{
		FPRINTF("[Line : %d][%s] place_id is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(place_index < 0)
	{
		FPRINTF("[Line : %d][%s] place_index is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(place_cnt < 0)
	{
		FPRINTF("[Line : %d][%s] place_cnt is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else
	{
		g_bGeofencemanagerCBParameter = true;
	}
	g_pszPlaceName = place_name;
	g_nPlaceIndex = place_index;
	g_nPlaceCnt = place_cnt;
	FPRINTF("[Line : %d][%s] place_name = %s, place_index = %d, place_cnt = %d NULL\\n", __LINE__, API_NAMESPACE,place_name,place_index,place_cnt);
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
	return true;
}

/**
 * @function 		GeofenceStateChangedCB
 * @description	 	Called for geofence state change
 * @parameter		geofence_id ;geofence_state_e;user_data : The user data passed from the foreach function
 * @return 			boolean value 
 */
void GeofenceStateChangedCB(int geofence_id, geofence_state_e state, void *user_data)
{
	g_bGeofencemanagerCBFlag = true;
	if(geofence_id < 0)
	{
		FPRINTF("[Line : %d][%s] geofence_id is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if((state<GEOFENCE_STATE_UNCERTAIN)||(state>GEOFENCE_STATE_OUT))
	{
		FPRINTF("[Line : %d][%s] state is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else
	{
		g_bGeofencemanagerCBParameter = true;
	}
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}

/**
 * @function 		ITs_geofence_manager_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_geofence_manager_startup(void)
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
 * @function 		ITs_geofence_manager_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_geofence_manager_cleanup(void)
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

/** @addtogroup	itc-geofence-manager-testcases
* @brief 		Integration testcases for module geofence-manager
* @ingroup		itc-geofence-manager
* @{
*/

//& purpose: Set unset geofence event callback
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_is_supported_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create geofecne manager
 * @scenario				create geofecne manager
 * @apicovered				geofence_manager_is_supported
 * @passcase				When geofence_manager_create is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition			None
 */
int ITc_geofence_manager_is_supported_p(void)
{
	START_TEST;
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);
	
	bool bIsSupported;
	
	//Target API
	int nRet = geofence_manager_is_supported(&bIsSupported);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_is_supported", GeofenceManagerGetError(nRet));
	FPRINTF("[Line : %d][%s] geofence_manager_is_supported returned value = %s\\n", __LINE__, API_NAMESPACE, bIsSupported ? "true" : "false");
	
	return 0;
}

//& purpose: Set unset geofence event callback
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_create_destroy_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				create geofecne manager
 * @scenario				create geofecne manager
 * @apicovered				geofence_manager_create, geofence_manager_destroy
 * @passcase				When geofence_manager_create is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			None
 * @postcondition			None
 */
int ITc_geofence_manager_create_destroy_p(void)
{
	START_TEST;
	
	int nRet = geofence_manager_destroy(g_hGeofenceManager);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_destroy", GeofenceManagerGetError(nRet));
	
	nRet = geofence_manager_create(&g_hGeofenceManager);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_create", GeofenceManagerGetError(nRet));
	CHECK_HANDLE(g_hGeofenceManager, "geofence_manager_create");
	
	return 0;
}

//& purpose: Set unset geofence event callback
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_set_unset_geofence_event_cb_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Set unset geofence event callback
 * @scenario				Set unset geofence event callback
 * @apicovered				geofence_manager_set_geofence_event_cb, geofence_manager_unset_geofence_event_cb, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_place, geofence_manager_set_geofence_event_cb is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_set_unset_geofence_event_cb_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	char *pszPlaceName = "SOME_PLACE";
	int nPlaceId = 0;
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;

	int nRet = geofence_manager_set_geofence_event_cb(g_hGeofenceManager, GeofenceEventCB, NULL);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_set_geofence_event_cb", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");
	
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceEventCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}

	nRet = geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_unset_geofence_event_cb", GeofenceManagerGetError(nRet));
	
	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	return 0;
}

//& purpose: Start stop geofence manager
//& type: auto
/**
 * @testcase 				ITc_geofence_manager_start_stop_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Start stop geofence manager
 * @scenario				Start stop geofence manager
 * @apicovered				geofence_manager_start, geofence_manager_stop, geofence_manager_unset_geofence_event_cb, geofence_manager_add_place, geofence_manager_remove_place
 * @passcase				When geofence_manager_set_geofence_event_cb, geofence_manager_start, geofence_manager_stop, geofence_manager_unset_geofence_event_cb is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_start_stop_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;
	int nPlaceId = 0, nFenceId = 0;
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

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_manager_set_geofence_state_changed_cb(g_hGeofenceManager, GeofenceStateChangedCB, NULL);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_set_geofence_state_changed_cb", GeofenceManagerGetError(nRet));

	nRet = geofence_manager_start(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_start", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceStateChangedCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
		return 1;
	}

	nRet = geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_unset_geofence_state_changed_cb", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	nRet = geofence_manager_stop(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_stop", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));
	
	return 0;
}

//& purpose: geofence manager API to add/update/remove place 
//& type: auto
/**
 * @testcase 				ITc_geofence_manager_add_update_remove_place_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				geofence manager API to add/update/remove place 
 * @scenario				geofence manager add place\n
 *							geofence manager update place\n
 *							geofence manager remove
 * @apicovered				geofence_manager_add_place, geofence_manager_update_place, geofence_manager_remove_place, geofence_manager_unset_geofence_event_cb
 * @passcase				When geofence_manager_add_place, geofence_manager_update_place, geofence_manager_remove_place, geofence_manager_unset_geofence_event_cb is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_add_update_remove_place_p(void)
{
	START_TEST;
	
	char *pszPlaceName = "SOME_PLACE";
	int nPlaceId = 0;
	g_bGeofencemanagerCBFlag = false;
	
	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	
	nRet = geofence_manager_update_place(g_hGeofenceManager, nPlaceId, pszPlaceName);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_update_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	
	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	return 0;
}

//& purpose: set/unset geofence state changed callback
//& type: auto
/**
 * @testcase 				ITc_geofence_manager_set_unset_geofence_state_changed_cb_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				geofence manager API to add/update/remove place 
 * @scenario				set geofence state changed callback\n
 *							unset geofence state changed callback
 * @apicovered				geofence_manager_add_place, geofence_manager_remove_place, geofence_manager_unset_geofence_event_cb
 * @passcase				When geofence_manager_set_geofence_state_changed_cb and geofence_manager_unset_geofence_state_changed_cb is successful
 * @failcase				If geofence_manager_set_geofence_state_changed_cb or geofence_manager_unset_geofence_state_changed_cb fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_set_unset_geofence_state_changed_cb_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;
	int nPlaceId = 0, nFenceId = 0;
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

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_manager_set_geofence_state_changed_cb(g_hGeofenceManager, GeofenceStateChangedCB, NULL);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_set_geofence_state_changed_cb", GeofenceManagerGetError(nRet));

	nRet = geofence_manager_start(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_start", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceStateChangedCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
		return 1;
	}

	nRet = geofence_manager_unset_geofence_state_changed_cb(g_hGeofenceManager);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_unset_geofence_state_changed_cb", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	nRet = geofence_manager_stop(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_stop", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

//& purpose: add remove fence
//& type: auto
/**
 * @testcase 				ITc_geofence_manager_add_remove_fence_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				add remove fence
 * @scenario				add remove fence
 * @apicovered				geofence_manager_add_fence, geofence_manager_remove_fence, geofence_manager_unset_geofence_event_cb, geofence_manager_add_place, geofence_manager_remove_place
 * @passcase				When geofence_manager_add_fence, geofence_manager_remove_fence, geofence_manager_unset_geofence_event_cb is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_add_remove_fence_p(void)
{
	START_TEST;
	
	int nPlaceId = 0, nFenceId = 0;
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

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	return 0;
}

//& purpose: Call geofence callback to get geofence list
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_foreach_geofence_list_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Call geofence callback to get geofence list
 * @scenario				Call geofence callback to get geofence list
 * @apicovered				geofence_manager_foreach_geofence_list
 * @passcase				When geofence_manager_foreach_geofence_list is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_foreach_geofence_list_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_manager_foreach_geofence_list(g_hGeofenceManager, GeofenceManagerFenceCB, NULL);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_foreach_geofence_list", GeofenceManagerGetError(nRet));
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceManagerFenceCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}
	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	
	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	return 0;
}

//& purpose: Call geofence callback to get geofence place list
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_foreach_place_geofence_list_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Call geofence callback to get geofence place list
 * @scenario				Call geofence callback to get geofence place list
 * @apicovered				geofence_manager_foreach_place_geofence_list, geofence_manager_add_place, geofence_manager_remove_place
 * @passcase				When all covered API are successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_foreach_place_geofence_list_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	int nPlaceId = 0, nFenceId = 0;
	char *pBssid = "88:30:8A:6C:28:16";
	geofence_h geofenceH = NULL;
	const char *pSsid = "WI-FI";
	char *pszPlaceName = "SOME_PLACE";
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pszPlaceName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_create_wifi(nPlaceId, pBssid, pSsid, &geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_create_wifi", GeofenceManagerGetError(nRet),geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_HANDLE(geofenceH, "geofence_create_wifi");

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");

	nRet = geofence_manager_foreach_place_geofence_list(g_hGeofenceManager, nPlaceId, GeofenceManagerFenceCB, NULL);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_foreach_place_geofence_list", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceManagerFenceCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}
	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager);geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	
	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet), geofence_manager_unset_geofence_event_cb(g_hGeofenceManager));

	return 0;
}

//& purpose: Call geofence callback to get place list
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_foreach_place_list_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Call geofence callback to get place list
 * @scenario				Call geofence callback to get place list
 * @apicovered				geofence_manager_foreach_place_list
 * @passcase				When geofence_manager_foreach_place_list is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_foreach_place_list_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;

	int nRet = geofence_manager_foreach_place_list(g_hGeofenceManager, GeofenceManagerPlaceCB, NULL);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_foreach_place_list", GeofenceManagerGetError(nRet));
	
	RUN_POLLING_LOOP;
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceManagerPlaceCB]\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		return 1;
	}
	
	return 0;
}

//& purpose: Get place name
//& type: auto

/**
 * @testcase 				ITc_geofence_manager_get_place_name_p
 * @since_tizen				2.4
 * @author					SRID(gaurav.m2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					auto
 * @description				Get place name
 * @scenario				Get place name
 * @apicovered				geofence_manager_add_place, geofence_manager_get_place_name, geofence_manager_remove_place
 * @passcase				When geofence_manager_get_place_name, geofence_manager_add_place, geofence_manager_get_place_name is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_get_place_name_p(void)
{
	START_TEST;

	g_bGeofencemanagerCBFlag = false;
	char *pszPlaceName = NULL;
	char *pplacName = "SOME_PLACE";
	int nPlaceId = 0;

	int nRet = geofence_manager_add_place(g_hGeofenceManager, pplacName, &nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_place", GeofenceManagerGetError(nRet));
	CHECK_VALUE_INT(nPlaceId, "geofence_manager_add_place");

	nRet = geofence_manager_get_place_name(g_hGeofenceManager, nPlaceId, &pszPlaceName);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_get_place_name", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	FPRINTF("[Line : %d][%s] pszPlaceName = %s\\n", __LINE__, API_NAMESPACE,pszPlaceName);
	if(pszPlaceName == NULL)
	{
		FPRINTF("[Line : %d][%s] output value is invalid\\n", __LINE__, API_NAMESPACE);
		geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
		return 1;
	}

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));

	return 0;
}

/**
 * @testcase 				ITc_geofence_manager_set_unset_geofence_proximity_state_changed_cb_p
 * @since_tizen				3.0
 * @author					SRID(nibha.sharma)
 * @reviewer				SRID(parshant.v)
 * @type 					auto
 * @description				Set and Unset proximity state
 * @scenario				Set proximity state and Unset proximity state
 * @apicovered				geofence_manager_set_geofence_proximity_state_changed_cb, geofence_manager_unset_geofence_proximity_state_changed_cb
 * @passcase				When geofence_manager_set_geofence_proximity_state_changed_cb and geofence_manager_unset_geofence_proximity_state_changed_cb is successful
 * @failcase				If target API fails or any precondition API fails
 * @precondition			geofence_manager_create
 * @postcondition			None
 */
int ITc_geofence_manager_set_unset_geofence_proximity_state_changed_cb_p(void)
{
	START_TEST;
	
	int nTimeoutId;
	g_bGeofencemanagerCBFlag = false;
	g_bGeofencemanagerCBParameter = false;
	int nPlaceId = 0, nFenceId = 0;
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

	nRet = geofence_manager_add_fence(g_hGeofenceManager, geofenceH, &nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_add_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_fence(g_hGeofenceManager, nFenceId));
	CHECK_HANDLE(geofenceH, "geofence_manager_add_fence");
	CHECK_VALUE_INT(nFenceId, "geofence_manager_add_fence");
	
	nRet = geofence_manager_set_geofence_proximity_state_changed_cb(g_hGeofenceManager, GeofenceProximityStateChangedCB, "data");
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_set_geofence_proximity_state_changed_cb", GeofenceManagerGetError(nRet));
	
	nRet = geofence_manager_start(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_start", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));
	
	RUN_POLLING_LOOP;
	
	if ( !g_bGeofencemanagerCBFlag )
	{
		FPRINTF("[Line : %d][%s] Callback failed [GeofenceProximityStateChangedCB]\\n", __LINE__, API_NAMESPACE);
		geofence_manager_unset_geofence_proximity_state_changed_cb(g_hGeofenceManager);
		return 1;
	}
	else if ( !g_bGeofencemanagerCBParameter )
	{
		geofence_manager_unset_geofence_proximity_state_changed_cb(g_hGeofenceManager);
		return 1;
	}
	
	nRet = geofence_manager_unset_geofence_proximity_state_changed_cb(g_hGeofenceManager);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_unset_geofence_proximity_state_changed_cb", GeofenceManagerGetError(nRet));
	
	nRet = geofence_manager_stop(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_stop", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_fence(g_hGeofenceManager, nFenceId);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_fence", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_destroy(geofenceH);
	PRINT_RESULT_CLEANUP(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_destroy", GeofenceManagerGetError(nRet), geofence_manager_remove_place(g_hGeofenceManager, nPlaceId));

	nRet = geofence_manager_remove_place(g_hGeofenceManager, nPlaceId);
	PRINT_RESULT(GEOFENCE_MANAGER_ERROR_NONE, nRet, "geofence_manager_remove_place", GeofenceManagerGetError(nRet));
	
	return 0;
}

/** @} */ //end of itc-geofence-manager
/** @} */ //end of itc-geofence-manager-testcases
