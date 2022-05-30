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
#ifndef _ITS_MAPS_SERVICE_COMMON_H_
#define _ITS_MAPS_SERVICE_COMMON_H_

#include "tct_common.h"
#include "assert.h"
#include <app.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <Evas.h>
#include <Elementary.h>
#include "maps_service.h"
#include "maps_address.h"
#include "maps_error.h"
#include "maps_area.h"
#include "maps_coordinates.h"
#include "maps_place_filter.h"
#include "maps_preference.h"
#include "maps_view.h"
//#include "maps_plugin_info.h"
#include <glib-object.h>
#include <glib-2.0/glib.h>

/** @addtogroup itc-maps-service
*  @ingroup itc
*  @{
*/
#define API_NAMESPACE				"MAPS_SERVICE_ITC"
#define BUFFER						50
#define GMAINTIMEOUT				30000 		//30 seconds
#define IMAGE_FILENAME 				"location_01_ic.png"
#define NEW_IMAGE_FILENAME 			"location_02_ic.png"
#define BUFF_LEN 					4096
#define RESULT 10
#define DISTANCE 504295
#define DISTANCELOC 500
#define LATITUTE_LOCATION 52.516071
#define LONGITUDE_LOCATION 13.376980
#define LATITUTE 52.5167
#define LONGITUDE 13.383
#define LATITUTE_ORG 37.564263
#define LONGITUDE_ORG 126.974676
#define LATITUTE_DEST 37.557120
#define LONGITUDE_DEST 126.992410

#define MAPS_FEATURE			"http://tizen.org/feature/maps"
#define INTERNET_FEATURE        "http://tizen.org/feature/network.internet"

bool g_bFeatureSupported;
bool g_bFeatureMismatch;
bool g_bFeatureNotSupported;
bool g_bStartupPre;
bool g_bCategoryCreate;
GMainLoop *g_pMainLoop;
bool gCheckBool;
char gszImagePath[BUFF_LEN];
int g_nCheckCb;
int g_nCheckRet;	
int g_nClone;
maps_place_h g_maps_place;
char g_szMapsProvider[BUFFER];
maps_service_h g_hMapService;
maps_preference_h g_hMapsPref;
char *g_szPlaceURI;
																								
#define START_TEST_PLACE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
	{\
		return 1;\
	}\
	if ( g_bFeatureNotSupported )\
	{\
		return 0;\
	}\
	if ( g_bStartupPre == false )\
	{\
		FPRINTF("[Line : %d][%s] Precondition failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_ROUTE {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
	{\
		return 1;\
	}\
	if ( g_bFeatureNotSupported )\
	{\
		return 0;\
	}\
	if ( g_bStartupPre == false )\
	{\
		FPRINTF("[Line : %d][%s] Precondition failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}
#define START_TEST(HANDLE, TYPE) {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
	{\
		return 1;\
	}\
	if ( g_bFeatureNotSupported )\
	{\
		return 0;\
	}\
	if ( HANDLE == NULL )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of %s failed\\n", __LINE__, API_NAMESPACE, TYPE);\
		return 1;\
	}\
}

#define START_TEST_VIEW(BOOLTYPE, TYPE) {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( BOOLTYPE == false )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of %s failed\\n", __LINE__, API_NAMESPACE, TYPE);\
	return 1;\
	}\
	if ( g_bFeatureMismatch )\
	{\
		return 1;\
	}\
	if ( g_bFeatureNotSupported )\
	{\
		return 0;\
	}\
}

#define START_TEST_PLACE_CATEGORY {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFeatureMismatch )\
	{\
		return 1;\
	}\
	if ( g_bFeatureNotSupported )\
	{\
		return 0;\
	}\
	if ( !g_bCategoryCreate )\
	{\
		FPRINTF("[Line : %d][%s] Precondition to create category handle failed so leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_OBJECT {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define COMPARE_STRING(pszSetStr, pszGetStr, API) {\
	if(pszGetStr != NULL) {\
		if ( strcmp(pszSetStr, pszGetStr) != 0)\
		{\
			FPRINTF("[Line : %d][%s] Mismatch in value, set = %s, get = %s\\n", __LINE__, API_NAMESPACE, pszSetStr, pszGetStr);\
			CHECK_VALUE_STRING(pszGetStr, API);\
			return 1;\
		}\
	}\
	else {\
		FPRINTF("[Line : %d][%s] Get value is NULL\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	int nTtimeoutId = g_timeout_add(GMAINTIMEOUT, MapsCallbackTimeout, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTtimeoutId);\
	g_pMainLoop = NULL;\
}


char *MapServiceGetError(int nRet);
gboolean MapsCallbackTimeout(gpointer data);
bool GetResourceDataPath(void);
void MapsPlaceHandleHelperHERE(void);
void MapsPlaceLocationHandleHelperHERE(void);
/** @} */
#endif  //_ITS_MAPS_SERVICE_COMMON_H_
