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
#ifndef __TCT_SENSOR-NATIVE_H__
#define __TCT_SENSOR-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_sensor_startup(void);
extern void CTs_sensor_cleanup(void);

extern int CTc_Sensor_SensorIsSupported_acceleration_p(void);
extern int CTc_Sensor_SensorIsSupported_Magnetic_p(void);
extern int CTc_Sensor_SensorIsSupported_light_p(void);
extern int CTc_Sensor_SensorIsSupported_gyroscope_p(void);
extern int CTc_Sensor_SensorIsSupported_Proximity_p(void);
extern int CTc_Sensor_SensorIsSupported_Gravity_p(void);
extern int CTc_Sensor_SensorIsSupported_Linear_Acceleration_p(void);
extern int CTc_Sensor_SensorIsSupported_Orientation_p(void);
extern int CTc_Sensor_SensorIsSupported_Rotation_Vector_p(void);

testcase tc_array[] = {
	{"CTc_Sensor_SensorIsSupported_acceleration_p",CTc_Sensor_SensorIsSupported_acceleration_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Magnetic_p",CTc_Sensor_SensorIsSupported_Magnetic_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_light_p",CTc_Sensor_SensorIsSupported_light_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_gyroscope_p",CTc_Sensor_SensorIsSupported_gyroscope_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Proximity_p",CTc_Sensor_SensorIsSupported_Proximity_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Gravity_p",CTc_Sensor_SensorIsSupported_Gravity_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Linear_Acceleration_p",CTc_Sensor_SensorIsSupported_Linear_Acceleration_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Orientation_p",CTc_Sensor_SensorIsSupported_Orientation_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{"CTc_Sensor_SensorIsSupported_Rotation_Vector_p",CTc_Sensor_SensorIsSupported_Rotation_Vector_p,CTs_sensor_startup,CTs_sensor_cleanup},
	{NULL, NULL}
};

#endif // __TCT_SENSOR-NATIVE_H__
