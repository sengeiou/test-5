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
#ifndef _ITS_LOCATION_MANAGER_COMMON_H_
#define _ITS_LOCATION_MANAGER_COMMON_H_

#include "tct_common.h"

//Add test package related includes here

#include <locations.h>
#include <glib.h>
#include <app.h>


/** @addtogroup itc-location-manager
*  @ingroup itc
*  @{
*/

bool g_bStartSuccess;
bool g_bCreateSuccess;

bool g_bIsWpsFeatureSupported;
bool g_bIsGpsFeatureSupported;
bool g_bIsLocationFeatureSupported;
bool g_bIsLocationManagerSupported;
bool g_bIsGPSSatelliteSupported;
bool g_bIsLocationBatchSupported;

bool g_bLocationMismatch;
bool g_bLocationNotSupported;
bool g_bCallbackHit;
bool g_bCallbackReturnValue;
bool g_bIsServiceEnabled;
bool g_bIsSatelliteEnabled;
GMainLoop *g_pLocationManagerMainLoop;
location_manager_h g_stManager;
bool g_bCleanupNotRequired;

/************************* Constant values macros **********************************/
#define API_NAMESPACE			"LOCATION_MANAGER_ITC"
#define TIMEOUT_CB				60000
#define SLEEP_TIME				3
#define LOCATION_FEATURE		"http://tizen.org/feature/location"
#define LOCATION_WPS_FEATURE	"http://tizen.org/feature/location.wps"
#define LOCATION_GPS_FEATURE	"http://tizen.org/feature/location.gps"
#define LOCATION_GPS_SATELLITE  "http://tizen.org/feature/location.gps.satellite"
#define LOCATION_BATCH			"http://tizen.org/feature/location.batch"


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
}

#define START_TEST_GPS {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bLocationMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_manager_create() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bLocationNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if(g_hLocationManager == NULL)\
	{\
		FPRINTF("[Line : %d][%s] g_hLocationManager is NULL \\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_MANAGER {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bLocationMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by location_manager_create() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bLocationNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if(g_stManager == NULL)\
	{\
		FPRINTF("[Line : %d][%s] g_stManager is NULL \\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_BATCH {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bIsLocationBatchSupported == false )\
	{\
		FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#define RUN_POLLING_LOOP {\
	if(g_bCallbackHit == false)\
	{\
		g_pLocationManagerMainLoop = g_main_loop_new(NULL, false);\
		nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pLocationManagerMainLoop);\
		g_main_loop_run(g_pLocationManagerMainLoop);\
		g_source_remove(nTimeoutId);\
		g_pLocationManagerMainLoop = NULL;\
	}\
}

//Add helper function declarations here

char* LocationManagerGetError(location_error_e nRet);
char* LocationBoundsGetError(location_bound_error_e nRet);

char* LocationManagerGetEnum(int nRet);

gboolean Timeout(gpointer data);

void LocationServiceStateChangeCb(location_service_state_e state, void *user_data);
void LocationServiceMethodStateChangeCb(location_service_state_e state, void *user_data);
void LocationGpsStatusSatelliteUpdatedCB(int num_of_active, int num_of_inview, time_t timestamp, void *user_data);

void LocationManagerCreateStart(location_manager_h *pstManager);
void LocationManagerStopDestroy(location_manager_h *pstManager);
void LocationManagerCreateStartMethod(location_manager_h *pstManager, location_method_e eLocationMethod);
void LocationManagerStopDestroyMethod(location_manager_h *pstManager);
void LocationManagerCreateMethodBatch(location_manager_h *pstManager, location_method_e eLocationMethod);
void LocationManagerDestroyMethod(location_manager_h *pstManager);

/** @} */
#endif  //_ITS_LOCATION_MANAGER_COMMON_H_
