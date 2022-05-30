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
#ifndef _SENSOR_COMMON_H_
#define _SENSOR_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <pthread.h>
#include <sensor.h>
#include <system_info.h>

/** @addtogroup ctc-sensor
* @ingroup		ctc
* @{
*/

static const int MIN_INTERVAL[] = {
	20, // Acceleration
	20, // Magnetic
	20, // Gyro 
	100, //Light(Photometer)
	100, //Proximity	
	100, //Gravity
	100, //Linear Acceleration
	100, //Orientation
	100 //Rotation Vector	
};

static const float DATA_RANGE[10][3] = {
	{-19.6,    19.6,     0.1}, // Acceleration
	{-1200, 1200,  1}, // Magnetic
	{-573.0, 573.0,  0.1}, // Gyroscope
	{0,     45000, 1}, // Light (Photometer)
	{0,     5,     1}, // Proximity
	{-19.6,     19.6,     0.1}, // Gravity
	{-19.6,     19.6,     0.1}, // Linear Acceleration
	{-360,     360,     1}, // Orientation
	{-1,     1,     1} // Rotation Vector
};

#define API_NAMESPACE			"SENSOR_CTC"
#define MAX_BLOCK_SIZE			20 
#define SENSOR_VALUE			1000

#define SENSOR_ACCELEROMETER_FEATURE		"http://tizen.org/feature/sensor.accelerometer"
#define SENSOR_GRAVITY_FEATURE				"http://tizen.org/feature/sensor.gravity"
#define SENSOR_LINEAR_ACCELERATION_FEATURE	"http://tizen.org/feature/sensor.linear_acceleration"
#define SENSOR_MAGNETIC_FEATURE				"http://tizen.org/feature/sensor.magnetometer"
#define SENSOR_ROTATION_VECTOR_FEATURE		"http://tizen.org/feature/sensor.rotation_vector"
#define SENSOR_ORIENTATION_FEATURE			"http://tizen.org/feature/sensor.tiltmeter"
#define SENSOR_GYROSCOPE_FEATURE			"http://tizen.org/feature/sensor.gyroscope"
#define SENSOR_LIGHT_FEATURE				"http://tizen.org/feature/sensor.photometer"
#define SENSOR_PROXIMITY_FEATURE			"http://tizen.org/feature/sensor.proximity"
#define SENSOR_PRESSURE_FEATURE				"http://tizen.org/feature/sensor.barometer"
#define SENSOR_ULTRAVIOLET_FEATURE			"http://tizen.org/feature/sensor.ultraviolet"
#define SENSOR_TEMPERATURE_FEATURE			"http://tizen.org/feature/sensor.temperature"
#define SENSOR_HUMIDITY_FEATURE				"http://tizen.org/feature/sensor.humidity"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

int g_nSensonrDelay;
bool g_bIsSupportedSensor;
sensor_type_e eSensorType;
sensor_h g_hSensor;
struct sensor_listener_s *g_listener;

enum sensorstype_e {
	ACCELERATION = 0,
	MAGNETIC,
	GYRO,
	LIGHT,
	PROXIMITY,
	GRAVITY,
	LINEAR_ACCELERATION,
	ORIENTATION,
	ROTATION_VECTOR,
	TILT
};
enum sensorspec_e {
	MIN_RANGE_SENSOR = 0,
	MAX_RANGE_SENSOR,
	RESOLUTION_SENSOR
};

//Add helper function declarations here
void SensorApiErrorInfo(char *pszApi,int nRet);
bool SensorCreate();
bool SensorCheckSupport(sensor_type_e eSensorType);
bool SensorGetDefaultSensor(sensor_type_e eSensorType);
bool SensorIsStart();
bool SensorStop();
bool SensorDestroy();
bool SensorUnsetcb();

/** @} */ //end of ctc-sensor

#endif  //_SENSOR_COMMON_H_