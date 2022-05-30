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

location_manager_h g_hLocationManagerBatch = NULL;
location_method_e g_eMethod = LOCATIONS_METHOD_GPS;
/**
* @function			Location_batch_cb
* @description		when the batch interval is expired.
* @parameter		int num_of_location, void *user_data
* @return			void
*/
static void Location_batch_cb(int num_of_location, void *user_data)
{
	FPRINTF("[Line : %d][%s] Location_batch_cb callback called\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}

	FPRINTF("[Line : %d][%s] The number of location :  %d \\n", __LINE__, API_NAMESPACE , num_of_location );
	return;
}

/**
* @function			location_batch_get_location_cb
* @description		Gets iteratively to receive location batch data.
* @parameter		double latitude, double longitude, double altitude, double speed, double direction, double horizontal, double vertical, time_t timestamp, void *user_data
* @return			bool	// To retrieve all location otherwise can set false
*
*/
static bool Location_batch_get_location_cb (double latitude, double longitude, double altitude, double speed, double direction, double horizontal, double vertical, time_t timestamp, void *user_data)
{
	FPRINTF("[Line : %d][%s] Location_batch_get_location_cb callback called\\n", __LINE__, API_NAMESPACE);
	FPRINTF("[Line : %d][%s] latitude : %lf , longitude : %lf , altitude : %lf , speed : %lf , direction : %lf , horizontal : %lf , vertical : %lf , time_t : %ld \\n", __LINE__, API_NAMESPACE , latitude, longitude, altitude, speed, direction, horizontal, vertical, timestamp);
	g_bCallbackHit = true;
	if ( g_pLocationManagerMainLoop )
	{
		g_main_loop_quit(g_pLocationManagerMainLoop);
	}

	// To retrieve all location otherwise can set false
	return true;
}

/**
* @function			ITs_location_batch_startup
* @description		Called before each test, set the service boolean true
* @parameter		NA
* @return			NA
*/
void ITs_location_batch_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bIsLocationBatchSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_BATCH, API_NAMESPACE);
	g_bIsLocationFeatureSupported = TCTCheckSystemInfoFeatureSupported(LOCATION_FEATURE, API_NAMESPACE);

	//Feature check for group of apis

	//Instance of location manager
	LocationManagerCreateMethodBatch(&g_hLocationManagerBatch, g_eMethod);
}

/**
* @function			ITs_location_batch_cleanup
* @description		Called after each test
* @parameter		NA
* @return			NA
*/
void ITs_location_batch_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Location_Manager_p\\n", __LINE__, API_NAMESPACE);
#endif

	LocationManagerDestroyMethod(&g_hLocationManagerBatch);
	return;
}


/** @addtogroup itc-location-batch-testcases
*  @brief		Integration testcases for module location-batch
*  @ingroup		itc-location-batch
*  @{
*/

//& purpose: To check start and stop of location batch service
//& type: auto
/**
* @testcase				ITc_location_start_stop_batch_p
* @since_tizen			3.0
* @author				SRID(sameer.g1)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			To check start and stop of location batch service
* @scenario				check start and stop of location batch service
*						start location batch service
*						stop location service
* @apicovered			location_manager_start_batch, location_manager_stop_batch
* @passcase				When both apis are successful
* @failcase				If targeted APIs fails
* @precondition			The location service state must be LOCATIONS_SERVICE_ENABLED with location_manager_start
* @postcondition		None
*/
int ITc_location_start_stop_batch_p(void)
{
	START_TEST_BATCH ;

	int nRet = location_manager_start_batch ( g_hLocationManagerBatch ); // Target API
	if ( !g_bIsLocationBatchSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_manager_start_batch() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_start_batch", LocationBoundsGetError(nRet));

	nRet = location_manager_stop_batch ( g_hLocationManagerBatch ); // Target API
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_stop_batch", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check all location information by invoking a specific callback for each location data.
//& type: auto
/**
* @testcase				ITc_location_manager_foreach_location_batch_p
* @since_tizen			3.0
* @author				SRID(sameer.g1)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			To check all location information by invoking a specific callback for each location data.
* @scenario				checked start location batch service \n
*						register location_manager_foreach_location_batch callback \n
*						checked stop location batch service \n
* @apicovered			location_manager_start_batch, location_manager_stop_batch ,
* @passcase				When targeted and supporting APIs are passed.
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_manager_foreach_location_batch_p(void)
{
	START_TEST_BATCH ;
	int nInterval = 1;
	int nDuration = 6;

	int nRet = location_manager_set_location_batch_cb(g_hLocationManagerBatch, Location_batch_cb , nInterval, nDuration , NULL); // Target API
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_location_batch_cb", LocationBoundsGetError(nRet));

	int nTimeoutId = 0;
	nRet = location_manager_start_batch ( g_hLocationManagerBatch );
	if (!g_bIsLocationBatchSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_manager_start_batch() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_start_batch", LocationBoundsGetError(nRet));

	// pre-initialization callback response
	g_bCallbackHit = false;
	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit)
	{
		FPRINTF("[Line : %d][%s] location_manager_foreach_location_batch unable to invoke callback function\\n", __LINE__, API_NAMESPACE);
		location_manager_stop_batch ( g_hLocationManagerBatch );
		return 1;
	}	// To retrieve all location otherwise can set false

	g_bCallbackHit = false;
	RUN_POLLING_LOOP;
	nRet = location_manager_foreach_location_batch(g_hLocationManagerBatch, Location_batch_get_location_cb , NULL); // Target API
	PRINT_RESULT_CLEANUP(LOCATIONS_ERROR_NONE, nRet, "location_manager_foreach_location_batch", LocationBoundsGetError(nRet) , location_manager_stop_batch ( g_hLocationManagerBatch ));

	nRet = location_manager_stop_batch ( g_hLocationManagerBatch );
	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_stop_batch", LocationBoundsGetError(nRet));

	nRet = location_manager_unset_location_batch_cb(g_hLocationManagerBatch);
	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_location_batch_cb", LocationBoundsGetError(nRet));

	return 0;
}

//& purpose: To check a callback function to be invoked when batch_period is expired.
//& type: auto
/**
* @testcase				ITc_location_manager_set_location_batch_cb_p
* @since_tizen			3.0
* @author				SRID(sameer.g1)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			To check a callback function to be invoked when batch_period is expired.
* @scenario				checked start location batch service \n
*						register location_manager_set_location_batch_cb callback \n
*						unregister callback from handler \n
*						checked stop location batch service \n
* @apicovered			location_manager_start_batch, location_manager_stop_batch, location_manager_set_location_batch_cb, location_manager_unset_location_batch_cb
* @passcase				When targeted and supporting APIs are passed.
* @failcase				If target API or supporting APIs fails
* @precondition			None
* @postcondition		None
*/
int ITc_location_manager_set_unset_location_batch_cb_p(void)
{
	START_TEST_BATCH ;
	int nRet = 0;
	int nInterval = 1;
	int nDuration = 6;
	int nTimeoutId = 0;

	nRet = location_manager_set_location_batch_cb(g_hLocationManagerBatch, Location_batch_cb , nInterval, nDuration , NULL); // Target API
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_set_location_batch_cb", LocationBoundsGetError(nRet));

	nRet = location_manager_start_batch ( g_hLocationManagerBatch );
	if (!g_bIsLocationBatchSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_manager_start_batch() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_start_batch", LocationBoundsGetError(nRet));

	// pre-initialization callback response
	g_bCallbackHit = false;
	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit)
	{
		FPRINTF("[Line : %d][%s] location_manager_set_location_batch_cb unable to invoke callback function\\n", __LINE__, API_NAMESPACE);
		location_manager_stop_batch ( g_hLocationManagerBatch );
		return 1;
	}

	nRet = location_manager_stop_batch ( g_hLocationManagerBatch );
	PRINT_RESULT(LOCATIONS_ERROR_NONE, nRet, "location_manager_stop_batch", LocationBoundsGetError(nRet));

	nRet = location_manager_unset_location_batch_cb(g_hLocationManagerBatch); // Target API
	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_unset_location_batch_cb", LocationBoundsGetError(nRet));

	return 0;
}
/** @} */
/** @} */
