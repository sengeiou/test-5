//
// Copyright (c) 2020 Samsung Electronics Co., Ltd.
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
#ifndef __TCT_SENSOR_COMMONH_H__
#define __TCT_SENSOR_COMMONH_H__

#include <sensor.h>
#include <dlog.h>

#define SENSOR_TYPES(F)                   \
    F(SENSOR_ACCELEROMETER)               \
    F(SENSOR_GRAVITY)                     \
    F(SENSOR_LINEAR_ACCELERATION)         \
    F(SENSOR_MAGNETIC)                    \
    F(SENSOR_ROTATION_VECTOR)             \
    F(SENSOR_ORIENTATION)                 \
    F(SENSOR_GYROSCOPE)                   \
    F(SENSOR_LIGHT)                       \
    F(SENSOR_PRESSURE)                    \
    F(SENSOR_ULTRAVIOLET)                 \
    F(SENSOR_TEMPERATURE)                 \
    F(SENSOR_HUMIDITY)                    \
    F(SENSOR_HRM)                         \
    F(SENSOR_HRM_LED_GREEN)               \
    F(SENSOR_HRM_LED_IR)                  \
    F(SENSOR_HRM_LED_RED)                 \
    F(SENSOR_GYROSCOPE_UNCALIBRATED)      \
    F(SENSOR_GEOMAGNETIC_UNCALIBRATED)    \
    F(SENSOR_GYROSCOPE_ROTATION_VECTOR)   \
    F(SENSOR_GEOMAGNETIC_ROTATION_VECTOR) \
    F(SENSOR_GYROSCOPE_ORIENTATION)       \
    F(SENSOR_GEOMAGNETIC_ORIENTATION)     \
    F(SENSOR_HRM_BATCH)                   \
    F(SENSOR_HRM_LED_GREEN_BATCH)

#define SENSOR_ERRORS(F)                 \
    F(SENSOR_ERROR_NONE)                 \
    F(SENSOR_ERROR_IO_ERROR)             \
    F(SENSOR_ERROR_INVALID_PARAMETER)    \
    F(SENSOR_ERROR_OUT_OF_MEMORY)        \
    F(SENSOR_ERROR_NOT_NEED_CALIBRATION) \
    F(SENSOR_ERROR_NOT_SUPPORTED)        \
    F(SENSOR_ERROR_OPERATION_FAILED)     \
    F(SENSOR_ERROR_PERMISSION_DENIED)    \
    F(SENSOR_ERROR_NO_DATA)              \
    F(SENSOR_ERROR_NOT_AVAILABLE)

char *sensor_type_e_to_str(sensor_type_e type);
char *sensor_error_to_str(int ret);

#endif