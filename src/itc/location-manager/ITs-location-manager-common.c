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

/**
* @function 		LocationManagerGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* LocationManagerGetError(location_error_e nRet)
{
	char *szErrorVal = NULL;
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
	//case LOCATIONS_ERROR_SETTING_OFF:					szErrorVal = "LOCATIONS_ERROR_SETTING_OFF";						break;
	default:											szErrorVal = "Unknown Error";									break;
	}

	return szErrorVal;
}

/**
* @function 		LocationBoundsGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* LocationBoundsGetError(location_bound_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case LOCATION_BOUNDS_ERROR_NONE:				szErrorVal = "LOCATION_BOUNDS_ERROR_NONE";					break;
	case LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY:		szErrorVal = "LOCATION_BOUNDS_ERROR_OUT_OF_MEMORY";			break;
	case LOCATION_BOUNDS_ERROR_INVALID_PARAMETER:	szErrorVal = "LOCATION_BOUNDS_ERROR_INVALID_PARAMETER";		break;
	case LOCATION_BOUNDS_ERROR_NOT_SUPPORTED:		szErrorVal = "LOCATION_BOUNDS_ERROR_NOT_SUPPORTED";			break;
	case LOCATION_BOUNDS_ERROR_INCORRECT_TYPE:		szErrorVal = "LOCATION_BOUNDS_ERROR_INCORRECT_TYPE";		break;
	case LOCATION_BOUNDS_ERROR_IS_ADDED:			szErrorVal = "LOCATION_BOUNDS_ERROR_IS_ADDED";				break;
	}

	return szErrorVal;
}

/**
* @function 		LocationManagerGetEnum
* @description	 	Maps  enumerators to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* LocationManagerGetEnum(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case LOCATIONS_METHOD_HYBRID:		szErrorVal = "LOCATIONS_METHOD_HYBRID";					break;
	case LOCATIONS_METHOD_GPS:			szErrorVal = "LOCATIONS_METHOD_GPS";					break;
	case LOCATIONS_METHOD_WPS:			szErrorVal = "LOCATIONS_METHOD_WPS";					break;
	case LOCATIONS_METHOD_PASSIVE: 		szErrorVal = "LOCATIONS_METHOD_PASSIVE";				break;
	default:							szErrorVal = "LOCATIONS_METHOD_NONE";					break;
	}

	return szErrorVal;
}

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		LocationManagerCreateStart
* @description	 	Create a message service and start it
* @parameter		pointer to location_manager_h structure
* @return 			NA
*/
void LocationManagerCreateStart(location_manager_h *pstManager)
{
	g_bCreateSuccess = false;
	g_bStartSuccess = false;
	g_bCallbackHit = false;

	int nTimeoutId = -1;
	int nRet = location_manager_create(LOCATIONS_METHOD_HYBRID, pstManager);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bLocationMismatch = true;
		}
		else
		{
			g_bLocationNotSupported = true;
		}
		return;
	}
	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
	if ( nRet == LOCATIONS_ERROR_NONE )
	{
		g_bCreateSuccess = true;
		nRet = location_manager_set_service_state_changed_cb(*pstManager, LocationServiceStateChangeCb, NULL);
		if ( nRet != LOCATIONS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] location_manager_set_service_state_changed_cb failed, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetError(nRet));
			return;
		}

		g_bCallbackReturnValue = false;
		g_bCallbackHit = false;
		nRet = location_manager_start(*pstManager);

		RUN_POLLING_LOOP;
		if ( g_bCallbackHit != true || g_bCallbackReturnValue != true)
		{
			FPRINTF("[Line : %d][%s] location_manager_start did not invoke service state change callback\\n", __LINE__, API_NAMESPACE);
			return;
		}

		PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_start", LocationManagerGetError(nRet));
		if ( nRet == LOCATIONS_ERROR_NONE )
		{
			g_bStartSuccess = true;
		}
	}
}

/**
* @function 		LocationManagerStopDestroy
* @description	 	stops a message service
* @parameter		pointer to location_manager_h structure
* @return 			NA
*/
void LocationManagerStopDestroy(location_manager_h *pstManager)
{
	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;
	int nTimeoutId = -1;
	if ( g_bStartSuccess )
	{
		location_manager_stop(*pstManager);
		g_bStartSuccess = false;
		RUN_POLLING_LOOP;
		if ( g_bCallbackHit != true || g_bCallbackReturnValue != true)
		{
			FPRINTF("[Line : %d][%s] location_manager_stop did not invoke service state change callback\\n", __LINE__, API_NAMESPACE);
		}
	}

	//sleep(SLEEP_TIME);
	if ( g_bCreateSuccess )
	{
		location_manager_unset_service_state_changed_cb(*pstManager);
		sleep(SLEEP_TIME);
		location_manager_destroy(*pstManager);
		g_bCreateSuccess = false;
	}
}

/**
* @function 		LocationManagerCreateStartMethod
* @description	 	Create a message service and start it
* @parameter		pointer to location_manager_h structure, location_method_e
* @return 			NA
*/
void LocationManagerCreateStartMethod(location_manager_h *pstManager, location_method_e eLocationMethod)
{
	g_bCreateSuccess = false;
	g_bStartSuccess = false;
	g_bCallbackHit = false;
	g_bIsServiceEnabled = false;
	g_bIsSatelliteEnabled = false;

	int nTimeoutId = -1;
	int nRet = location_manager_create(eLocationMethod, pstManager);
	if ( false == g_bIsLocationManagerSupported )
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			g_bLocationMismatch = true;
		}
		else
		{
			g_bLocationNotSupported = true;
		}
		return;
	}

	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
	if ( nRet == LOCATIONS_ERROR_NONE )
	{
		g_bCreateSuccess = true;
		nRet = location_manager_set_service_state_changed_cb(*pstManager, LocationServiceMethodStateChangeCb, NULL);
		if ( nRet != LOCATIONS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] location_manager_set_service_state_changed_cb failed, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetError(nRet));
			return;
		}

		nRet = gps_status_set_satellite_updated_cb(*pstManager, LocationGpsStatusSatelliteUpdatedCB, 1, NULL);
		if ( nRet != LOCATIONS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] gps_status_set_satellite_updated_cb failed, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetError(nRet));
			return;
		}

		g_bCallbackHit = false;
		nRet = location_manager_start(*pstManager);

		RUN_POLLING_LOOP;
		if ( g_bCallbackHit != true )
		{
			FPRINTF("[Line : %d][%s] location_manager_start did not invoke service state change callback\\n", __LINE__, API_NAMESPACE);
			return;
		}

		if ( g_bIsServiceEnabled != true )
		{
			FPRINTF("[Line : %d][%s] Service not enabled\\n", __LINE__, API_NAMESPACE);
			return;
		}
		if ( g_bIsSatelliteEnabled != true )
		{
			FPRINTF("[Line : %d][%s] Satellite not enabled\\n", __LINE__, API_NAMESPACE);
			return;
		}

		PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_start", LocationManagerGetError(nRet));
		if ( nRet == LOCATIONS_ERROR_NONE )
		{
			g_bStartSuccess = true;
		}
	}
}

/**
* @function 		LocationManagerStopDestroyMethod
* @description	 	stops a message service
* @parameter		pointer to location_manager_h structure
* @return 			NA
*/
void LocationManagerStopDestroyMethod(location_manager_h *pstManager)
{
	g_bCallbackHit = false;
	g_bCallbackReturnValue = false;
	int nTimeoutId = -1;
	if ( g_bStartSuccess )
	{
		location_manager_stop(*pstManager);
		g_bStartSuccess = false;
		RUN_POLLING_LOOP;
		if ( g_bCallbackHit != true || g_bCallbackReturnValue != true)
		{
			FPRINTF("[Line : %d][%s] location_manager_stop did not invoke service state change callback\\n", __LINE__, API_NAMESPACE);
		}
		if ( g_bIsServiceEnabled != false )
		{
			FPRINTF("[Line : %d][%s] Service not disabled\\n", __LINE__, API_NAMESPACE);
		}
	}

	//sleep(SLEEP_TIME);
	if ( g_bCreateSuccess )
	{
		gps_status_unset_satellite_updated_cb(*pstManager);
		sleep(SLEEP_TIME);
		location_manager_unset_service_state_changed_cb(*pstManager);
		sleep(SLEEP_TIME);
		location_manager_destroy(*pstManager);
		g_bCreateSuccess = false;
	}
}

/**
* @function			LocationManagerCreateMethodBatch
* @description		Create a message service
* @parameter		pointer to location_manager_h structure, location_method_e
* @return			NA
*/
void LocationManagerCreateMethodBatch(location_manager_h *pstManager, location_method_e eLocationMethod)
{
	g_bCreateSuccess = false;

	int nTimeoutId = -1;
	int nRet = location_manager_create(eLocationMethod, pstManager);

	PRINT_RESULT_NORETURN(LOCATIONS_ERROR_NONE, nRet, "location_manager_create", LocationManagerGetError(nRet));
	if ( nRet == LOCATIONS_ERROR_NONE )
	{
		g_bCreateSuccess = true;
		nRet = location_manager_set_service_state_changed_cb(*pstManager, LocationServiceMethodStateChangeCb, NULL);
		if ( nRet != LOCATIONS_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] location_manager_set_service_state_changed_cb failed, error returned = %s\\n", __LINE__, API_NAMESPACE, LocationManagerGetError(nRet));
			return;
		}
	}
}

/**
* @function			LocationManagerDestroyMethod
* @description		Destroy a location handle
* @parameter		pointer to location_manager_h structure
* @return			NA
*/
void LocationManagerDestroyMethod(location_manager_h *pstManager)
{
	//sleep(SLEEP_TIME);
	if ( g_bCreateSuccess )
	{
		location_manager_unset_service_state_changed_cb(*pstManager);
		sleep(SLEEP_TIME);
		location_manager_destroy(*pstManager);
		g_bCreateSuccess = false;
	}
}
/** @} */
