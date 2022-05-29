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
#include "ITs-geofence-manager-common.h"

//Add helper function definitions here

/** @addtogroup itc-geofence-manager
* @ingroup		itc
* @{
*/


/**
 * @function 		GeofenceManagerGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char* GeofenceManagerGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
		case GEOFENCE_MANAGER_ERROR_NONE:					szErrorVal = "GEOFENCE_MANAGER_ERROR_NONE";						break;
		case GEOFENCE_MANAGER_ERROR_OUT_OF_MEMORY:			szErrorVal = "GEOFENCE_MANAGER_ERROR_OUT_OF_MEMORY";			break;
		case GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER:		szErrorVal = "GEOFENCE_MANAGER_ERROR_INVALID_PARAMETER";		break;
		case GEOFENCE_MANAGER_ERROR_PERMISSION_DENIED:		szErrorVal = "GEOFENCE_MANAGER_ERROR_PERMISSION_DENIED";		break;
		case GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED:			szErrorVal = "GEOFENCE_MANAGER_ERROR_NOT_SUPPORTED";			break;
		case GEOFENCE_MANAGER_ERROR_NOT_INITIALIZED:		szErrorVal = "GEOFENCE_MANAGER_ERROR_NOT_INITIALIZED";			break;
		//case GEOFENCE_MANAGER_ERROR_ID_NOT_EXIST:			szErrorVal = "GEOFENCE_MANAGER_ERROR_ID_NOT_EXIST";				break;
		case GEOFENCE_MANAGER_ERROR_EXCEPTION:				szErrorVal = "GEOFENCE_MANAGER_ERROR_EXCEPTION";				break;
		case GEOFENCE_MANAGER_ERROR_ALREADY_STARTED:		szErrorVal = "GEOFENCE_MANAGER_ERROR_ALREADY_STARTED";			break;
		case GEOFENCE_MANAGER_ERROR_TOO_MANY_GEOFENCE:		szErrorVal = "GEOFENCE_MANAGER_ERROR_TOO_MANY_GEOFENCE";		break;
		case GEOFENCE_MANAGER_ERROR_IPC:					szErrorVal = "GEOFENCE_MANAGER_ERROR_IPC";						break;
		case GEOFENCE_MANAGER_ERROR_DATABASE:				szErrorVal = "GEOFENCE_MANAGER_ERROR_DATABASE";					break;
		default:											szErrorVal = "GEOFENCE_MANAGER_ERROR_UNKNOWN";					break;
	}
	return szErrorVal;
}

/**
 * @function 		GeofenceManagerTimeout
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */ 
gboolean GeofenceManagerTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n",__LINE__, API_NAMESPACE);
	return false;
}

/**
* @function 		GeofenceManagerCheckFeature
* @description	 	Checks if the location feature is supported, unsupported or mismatched
* @parameter		feature : location feature
* @return 			feature_check_e value
*/
feature_check_e GeofenceManagerCheckFeature(char* feature)
{
	bool bIsFeatureSupported = TCTCheckSystemInfoFeatureSupported(feature, API_NAMESPACE);
	bool bSupported = false;

	int nRet = geofence_manager_is_supported(&bSupported);
	if ( nRet != GEOFENCE_MANAGER_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] geofence_manager_is_supported failed for feature %s, error returned = %s\\n", __LINE__, API_NAMESPACE, feature, GeofenceManagerGetError(nRet));
		return FEATURE_MISMATCH;
	}
	if ( bIsFeatureSupported != bSupported )
	{
		FPRINTF("[Line : %d][%s] geofence_manager_is_supported return value (%s) mismatched with expected value (%s) for feature %s\\n", __LINE__, API_NAMESPACE, bSupported ? "true": "false", bIsFeatureSupported ? "true": "false", feature);
		return FEATURE_MISMATCH;
	}
	
	if ( bSupported )
	{
		FPRINTF("[Line : %d][%s] Feature %s is supported on device\\n", __LINE__, API_NAMESPACE, feature);
		return FEATURE_SUPPORTED;
	}
	
	FPRINTF("[Line : %d][%s] Feature %s is unsupported on device. Skipping test\\n", __LINE__, API_NAMESPACE, feature);
	
	return FEATURE_UNSUPPORTED;
}

/** @addtogroup itc-geofence-common
* @ingroup		itc
* @{
*/

/**
 * @function 		GeofenceEventCB
 * @description	 	Called for geo fence event
 * @parameter		int place_id : The location id;geofence_id ;geofence_manager_error_e : The geofence manager error return;user_data : The user data passed from the foreach function
 * @return 			boolean value 
 */
void GeofenceEventCB(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data)
{
	g_bGeofencemanagerCBFlag = true;
	if(place_id < 0)
	{
		FPRINTF("[Line : %d][%s] place_id is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(error != GEOFENCE_MANAGER_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] error is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(manage < 0)
	{
		FPRINTF("[Line : %d][%s] manage is not valid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else
	{
		g_bGeofencemanagerCBParameter = true;
	}
	g_nPlaceId = place_id;
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
}

/**
 * @function 		GeofenceManagerFenceCB
 * @description	 	Called for geo fence manager callback
 * @parameter		geofence_h : The fence;geofence_id ;fence_index : fencing index;user_data : The user data passed from the foreach function
 * @return 			boolean value 
 */
bool GeofenceManagerFenceCB(int geofence_id, geofence_h fence, int fence_index, int fence_cnt, void *user_data)
{
	g_bGeofencemanagerCBFlag = true;
	if ( fence == NULL )
	{
		FPRINTF("[Line : %d][%s] handle fence is NULL\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(geofence_id < 0)
	{
		FPRINTF("[Line : %d][%s] geofence_id is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(fence_index < 0)
	{
		FPRINTF("[Line : %d][%s] fence_index is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else if(fence_cnt < 0)
	{
		FPRINTF("[Line : %d][%s] fence_cnt is invalid\\n", __LINE__, API_NAMESPACE);
		g_bGeofencemanagerCBParameter = false;
	}
	else
	{
		g_bGeofencemanagerCBParameter = true;
	}
	
	g_hGeofence = fence;
	g_nGeofenceId = geofence_id;
	if ( g_loop != NULL )
	{
		g_main_loop_quit(g_loop);
		g_loop = NULL;
	}
	return true;
}
/** @} */ //end of itc-geofence-manager