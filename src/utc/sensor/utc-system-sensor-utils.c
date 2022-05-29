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
#include "assert.h"
#include <sensor.h>
#include <system_info.h>

//& set: SensorUtil

#define TEST_STRING "TEST_TEST_TEST"
static bool supported=false;
#define DEFAULT_VALUE 1

#define SENSOR_CNT 12
#define MANUAL_SENSOR_CNT 1

static char* sensor_features[12] = {
"http://tizen.org/feature/sensor.accelerometer",
"http://tizen.org/feature/sensor.gravitiy",
"http://tizen.org/feature/sensor.linear_acceleation",
"http://tizen.org/feature/sensor.magnetometer",
"http://tizen.org/feature/sensor.rotation_vector",
"http://tizen.org/feature/sensor.tiltmeter",
"http://tizen.org/feature/sensor.gyroscope",
"http://tizen.org/feature/sensor.photometer",
"http://tizen.org/feature/sensor.barometer",
"http://tizen.org/feature/sensor.ultraviolet",
"http://tizen.org/feature/sensor.temperature",
"http://tizen.org/feature/sensor.humidity"
};

static char* manual_sensor_features[] = {
"http://tizen.org/feature/sensor.proximity",
};

/**
 * @function		utc_system_sensor_util_startup
 * @description		Called before each test
 * @parameter		NA
 * @return			NA
 */
void utc_system_sensor_util_startup(void)
{
    int i;

    for(i=0;i<SENSOR_CNT;i++){

	 system_info_get_platform_bool(sensor_features[i], &supported);
	 if(supported) break;
    }
}

/**
 * @testcase		utc_system_sensor_util_get_angle_change_p
 * @since_tizen		2.3
 * @description		Computes the angle change between two rotation matrices.
 */
int utc_system_sensor_util_get_angle_change_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float R[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    float prevR[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    float angle[3];

    error = sensor_util_get_angle_change(R, prevR, angle);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_angle_change_n
 * @since_tizen		2.3
 * @description		Computes the angle change between two rotation matrices with invalid parameter.
 */
int utc_system_sensor_util_get_angle_change_n(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_util_get_angle_change(NULL, NULL, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_declination_p
 * @since_tizen		2.3
 * @description		Gets the declination of the horizontal component of the magnetic field from true north, in degrees.
 */
int utc_system_sensor_util_get_declination_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float latitude = DEFAULT_VALUE;
    float longitude = DEFAULT_VALUE;
    float altitude = DEFAULT_VALUE;
    float declination;

    error = sensor_util_get_declination(latitude, longitude, altitude, &declination);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_declination_n
 * @since_tizen		2.3
 * @description		Gets the declination of the horizontal component of the magnetic field from true north, in degrees with invalid parameter.
 */
int utc_system_sensor_util_get_declination_n(void)
{
    int error = SENSOR_ERROR_NONE;
    float latitude = DEFAULT_VALUE;
    float longitude = DEFAULT_VALUE;
    float altitude = DEFAULT_VALUE;

    error = sensor_util_get_declination(latitude, longitude, altitude, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_inclination_p
 * @since_tizen		2.3
 * @description		Computes the geomagnetic inclination angle in radians from the inclination matrix I returned by sensor_util_get_rotation_matrix().
 */
int utc_system_sensor_util_get_inclination_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float I[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    float inclination;

    error = sensor_util_get_inclination(I, &inclination);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_inclination_n
 * @since_tizen		2.3
 * @description		Computes the geomagnetic inclination angle in radians from the inclination matrix I returned by sensor_util_get_rotation_matrix() with invalid parameter.
 */
int utc_system_sensor_util_get_inclination_n(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_util_get_inclination(NULL, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_orientation_p
 * @since_tizen		2.3
 * @description		Computes the device's orientation based on the rotation matrix.
 */
int utc_system_sensor_util_get_orientation_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float R[9] = { 1, 1, 1, 1, 1, 1, 1, 1, 1 };
    float values[3];

    error = sensor_util_get_orientation(R, values);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_orientation_n
 * @since_tizen		2.3
 * @description		Computes the device's orientation based on the rotation matrix with invalid parameter.
 */
int utc_system_sensor_util_get_orientation_n(void)
{
    int error = SENSOR_ERROR_NONE;

    error = sensor_util_get_orientation(NULL, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_rotation_matrix_p
 * @since_tizen		2.3
 * @description		Gets the Inclination matrix "I" and Rotation matrix "R" transforming a vector from the device coordinate to the world's coordinate.
 */
int utc_system_sensor_util_get_rotation_matrix_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float Gx = DEFAULT_VALUE;
    float Gy = 0;
    float Gz = 0;
    float Mx = 0;
    float My = 0;
    float Mz = DEFAULT_VALUE;
    float R[9];
    float I[9];

    error = sensor_util_get_rotation_matrix(Gx, Gy, Gz, Mx, My, Mz, R, I);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_rotation_matrix_n
 * @since_tizen		2.3
 * @description		Gets the Inclination matrix "I" and Rotation matrix "R" transforming a vector from the device coordinate to the world's coordinate with invalid parameter.
 */
int utc_system_sensor_util_get_rotation_matrix_n(void)
{
    int error = SENSOR_ERROR_NONE;
    float Gx = DEFAULT_VALUE;
    float Gy = DEFAULT_VALUE;
    float Gz = DEFAULT_VALUE;
    float Mx = DEFAULT_VALUE;
    float My = DEFAULT_VALUE;
    float Mz = DEFAULT_VALUE;

    error = sensor_util_get_rotation_matrix(Gx, Gy, Gz, Mx, My, Mz, NULL, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_rotation_matrix_from_vector_p
 * @since_tizen		2.3
 * @description		Converts a rotation vector to a rotation matrix.
 */
int utc_system_sensor_util_get_rotation_matrix_from_vector_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float Vx = DEFAULT_VALUE;
    float Vy = DEFAULT_VALUE;
    float Vz = DEFAULT_VALUE;
    float R[9];

    error = sensor_util_get_rotation_matrix_from_vector(Vx, Vy, Vz, R);

    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_rotation_matrix_from_vector_n
 * @since_tizen		2.3
 * @description		Converts a rotation vector to a rotation matrix with invalid parameter.
 */
int utc_system_sensor_util_get_rotation_matrix_from_vector_n(void)
{
    int error = SENSOR_ERROR_NONE;
    float Vx = DEFAULT_VALUE;
    float Vy = DEFAULT_VALUE;
    float Vz = DEFAULT_VALUE;

    error = sensor_util_get_rotation_matrix_from_vector(Vx, Vy, Vz, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

static bool is_matrix_equal(float *left, float *right)
{
	int i;
	for (i = 0; i < 9; ++i) {
		if (left[i] != right[i])
			return false;
	}

	return true;
}

/**
 * @testcase		utc_system_sensor_util_remap_coordinate_system_p
 * @since_tizen		2.3
 * @description		Rotates the supplied rotation matrix so that it is expressed in a different coordinate system.
 */
int utc_system_sensor_util_remap_coordinate_system_p(void)
{
	int error = SENSOR_ERROR_NONE;
	float inR[9] = {1, 0, 0, 0, 0, -1, 0, 1, 0};
	float outR[9];
	float expected_x_y[9] = {1, 0, 0, 0, 0, -1, 0, 1, 0};
	float expected_y_x[9] = {0, 1, 0, 0, 0, 1, 1, 0, 0};
	float expected_z_x[9] = {0, 0, 1, 0, -1, 0, 1, 0, 0};
	float expected_y_z[9] = {0, 1, 0, -1, 0, 0, 0, 0, 1};
	float expected_z_y[9] = {0, 0, 1, 1, 0, 0, 0, 1, 0};
	float expected_my_x[9] = {0, -1, 0, 0, 0, -1, 1, 0, 0};
	float expected_my_mx[9] = {0, -1, 0, 0, 0, 1, -1, 0, 0};
	float expected_mz_x[9] = {0, 0, -1, 0, 1, 0, 1, 0, 0};
	float expected_mz_mx[9] = {0, 0, -1, 0, -1, 0, -1, 0, 0};

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_X, SENSOR_UTIL_AXIS_Y, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_x_y), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_Y, SENSOR_UTIL_AXIS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_y_x), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_Z, SENSOR_UTIL_AXIS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_z_x), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_Y, SENSOR_UTIL_AXIS_Z, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_y_z), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_Z, SENSOR_UTIL_AXIS_Y, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_z_y), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_MINUS_Y, SENSOR_UTIL_AXIS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_my_x), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_MINUS_Y, SENSOR_UTIL_AXIS_MINUS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_my_mx), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_MINUS_Z, SENSOR_UTIL_AXIS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_mz_x), true);

	error = sensor_util_remap_coordinate_system(inR, SENSOR_UTIL_AXIS_MINUS_Z, SENSOR_UTIL_AXIS_MINUS_X, outR);
	assert_eq(error, SENSOR_ERROR_NONE);
	assert_eq(is_matrix_equal(outR, expected_mz_mx), true);

	return 0;
}

/**
 * @testcase		utc_system_sensor_util_remap_coordinate_system_n
 * @since_tizen		2.3
 * @description		Rotates the supplied rotation matrix so that it is expressed in a different coordinate system with invalid parameter.
 */
int utc_system_sensor_util_remap_coordinate_system_n(void)
{
    int error = SENSOR_ERROR_NONE;
    sensor_util_axis_e x = sensor_util_axis_x;
    sensor_util_axis_e y = sensor_util_axis_y;

    error = sensor_util_remap_coordinate_system(NULL, x, y, NULL);

    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_altitude_p
 * @since_tizen		4.0
 * @description		Gets the altitude from the atmospheric pressure, the pressure at sea level and temperature.
 */
int utc_system_sensor_util_get_altitude_p(void)
{
    int error = SENSOR_ERROR_NONE;
    float pressure = 1000.0;
    float sea_level_pressure = 1013.25; /* Standard sea level pressure */
    float temperature = 15;
    float altitude;

    error = sensor_util_get_altitude(pressure, sea_level_pressure, temperature, &altitude);
    assert_eq(error, SENSOR_ERROR_NONE);

    return 0;
}

/**
 * @testcase		utc_system_sensor_util_get_altitude_n
 * @since_tizen		4.0
 * @description		Gets the altitude with invalid parameter
 */
int utc_system_sensor_util_get_altitude_n(void)
{
    int error = SENSOR_ERROR_NONE;
    float pressure = 1000.0;
    float sea_level_pressure = 1013.25; /* Standard sea level pressure */
    float temperature = 15;

    error = sensor_util_get_altitude(pressure, sea_level_pressure, temperature, NULL);
    assert_eq(error, SENSOR_ERROR_INVALID_PARAMETER);

    return 0;
}
