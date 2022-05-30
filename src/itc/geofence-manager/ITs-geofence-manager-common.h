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
#ifndef _ITS_GEOFENCE_MANAGER_COMMON_H_
#define _ITS_GEOFENCE_MANAGER_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include <geofence_manager.h>
#include <glib.h>
#include <app.h>

/** @addtogroup itc-geofence-manager
* @ingroup		itc
* @{
*/

#define API_NAMESPACE				"GEOFENCE_MANAGER_ITC"
#define TIMEOUT_CB 					30000
#define PATH_LEN					1024
#define GMAINTIMEOUT				30000 		//30 seconds
#define LOCATION_GEOFENCE_FEATURE	"http://tizen.org/feature/location.geofence"

typedef enum FeatureCheck {
	FEATURE_SUPPORTED = 0,
	FEATURE_UNSUPPORTED,
	FEATURE_MISMATCH
} feature_check_e;

GMainLoop *g_loop;
bool g_bIsGeofenceCreated;
bool g_bGeofencemanagerCBFlag;
bool g_bFeatureMismatch;
bool g_bFeatureNotSupported;
bool g_bGeofencemanagerCBParameter;
geofence_manager_h g_hGeofenceManager;
geofence_h g_hGeofence;

int g_nGeofenceId;
int g_nPlaceId;
const char *g_pszPlaceName;
int	g_nPlaceIndex;
int	g_nPlaceCnt;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureNotSupported ) {\
		return 0;\
	}\
	if ( g_bFeatureMismatch ) {\
		return 1;\
	}\
	if ( !g_bIsGeofenceCreated )\
	{\
		return 1;\
	}\
}
	
#define RUN_POLLING_LOOP {\
	if ( g_bGeofencemanagerCBFlag == false )\
	{\
		g_loop = g_main_loop_new(NULL, false);\
		nTimeoutId = g_timeout_add(TIMEOUT_CB, GeofenceManagerTimeout, g_loop);\
		g_main_loop_run(g_loop);\
		g_source_remove(nTimeoutId);\
		g_loop = NULL;\
	}\
}

//Add helper function declarations here

char *GeofenceManagerGetError(int nRet);
gboolean GeofenceManagerTimeout(gpointer data);
feature_check_e GeofenceManagerCheckFeature(char* feature);
void GeofenceEventCB(int place_id, int geofence_id, geofence_manager_error_e error, geofence_manage_e manage, void *user_data);
bool GeofenceManagerFenceCB(int geofence_id, geofence_h fence, int fence_index, int fence_cnt, void *user_data);

/** @} */ //end of itc-geofence-manager
#endif  //_ITS_GEOFENCE_MANAGER_COMMON_H_
