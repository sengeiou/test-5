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
#ifndef _ITS_SENSOR_COMMON_H_
#define _ITS_SENSOR_COMMON_H_

#include "tct_common.h"
#include <glib.h>
#include <glib-object.h>
#include <system_info.h>
#include <sensor.h>

/** @addtogroup itc-sensor
*  @ingroup itc
*  @{
*/
#define API_NAMESPACE				"SENSOR_ITC"
#define PATH_LEN					1024
#define MICROSECONDS_PER_SECOND		1000000
#define TIME_1_HOUR_SEC 3600
#define TIME_1_DAY_SEC (TIME_1_HOUR_SEC * 24)
#define TIME_1_MONTH_SEC (TIME_1_DAY_SEC * 30)

bool g_bSensorsCreation;
sensor_h g_pstSensorHandle;
sensor_listener_h g_pstSensorListener;
GMainLoop *g_pSensorMainLoop;

typedef struct Sensor
{
	sensor_type_e eSensorType;
	char szFeature[PATH_LEN];
} SensorFeature;

typedef enum FeatureCheck {
	FEATURE_SUPPORTED = 0,
	FEATURE_UNSUPPORTED,
	FEATURE_MISMATCH
} feature_check_e;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define RUN_POLLING_LOOP {\
	g_pSensorMainLoop = g_main_loop_new(NULL, false);\
	nSensorTimeoutId = g_timeout_add(nTimeOutCB, SensorTimeout, g_pSensorMainLoop);\
	g_main_loop_run(g_pSensorMainLoop);\
	g_source_remove(nSensorTimeoutId);\
	g_pSensorMainLoop = NULL;\
}

char* SensorOption(sensor_option_e nRet);
char* SensorGetType(sensor_type_e nRet);
gboolean SensorTimeout(gpointer data);
char* SensorsGetError(int nRet);
feature_check_e SensorCheckFeature(sensor_type_e sensor, char* feature);
char* SensorAttributeOption(sensor_attribute_e nSensorAttrOption);
/** @} */
#endif  //_ITS_SENSOR_COMMON_H_
