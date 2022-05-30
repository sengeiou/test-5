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
#include "ITs-sensor-common.h"

/**
* @function 		ITs_Sensors_startup
* @description	 	Called before each test, creates Sensors 
* @parameter		NA
* @return 			NA
*/ 
void ITs_sensor_util_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_Sensors_cleanup
* @description	 	Called after each test, destroys Sensors 
* @parameter		NA
* @return 			NA
*/ 
void ITs_sensor_util_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Sensor_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-sensor-testcases
*  @brief 		Integration testcases for module sensor
*  @ingroup 	itc-sensor
*  @{
*/
//& purpose: To compute the angle Change between two rotation matrices. 
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_angle_change_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To compute the angle Change between two rotation matrices.
* @scenario				Set the current and previous rotation matrix\n
*						Make an array to store the changes
* @apicovered			sensor_util_get_angle_change				
* @passcase				When sensor_util_get_angle_Change is successful
* @failcase				If target API sensor_util_get_angle_Change fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_angle_change_p(void)
{
	START_TEST;

	float fCurrentR[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	float fPrevR[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	float fAngleChange[3];

	// Target API
	int nRet = sensor_util_get_angle_change(fCurrentR, fPrevR,fAngleChange);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_angle_change", SensorsGetError(nRet));

	return 0;
}

//& purpose: To get the declination of the horizontal component of the magnetic field from true north in degrees
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_declination_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get the declination of the horizontal component of the magnetic field from true north in degrees 
* @scenario				Set the latitude longitude and altitude\n
*						Get the declination 
* @apicovered			sensor_util_get_declination				
* @passcase				When sensor_util_get_declination is successful
* @failcase				If target API sensor_util_get_declination fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_declination_p(void)
{
	START_TEST;

	float fLatitude = 5.23;
	float fLongitude = 10.34;
	float fAltitude = 15.65;
	float fDeclination;

	// Target API
	int nRet = sensor_util_get_declination(fLatitude, fLongitude, fAltitude, &fDeclination);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_declination", SensorsGetError(nRet));

	return 0;
}

//& purpose: To compute the device's orientation based on the rotation matrix
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_orientation_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To compute the device's orientation based on the rotation matrix
* @scenario				Set the rotation matrix in the array\n
*						Create an array of 3 floats to hold the result
* @apicovered			sensor_util_get_orientation				
* @passcase				When sensor_util_get_orientation is successful
* @failcase				If target API sensor_util_get_orientation fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_orientation_p(void)
{
	START_TEST;

	float fR[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	float fValues[3];

	// Target API
	int nRet = sensor_util_get_orientation(fR, fValues);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_orientation", SensorsGetError(nRet));

	return 0;
}

//& purpose: To get Inclination matrix and Rotation matrix transforming a vector from the device coordinate to the world's coordinate.
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_rotation_matrix_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To get Inclination matrix and Rotation matrix transforming a vector from the device coordinate to the world's coordinate.
* @scenario				Set X, Y,and Z-axis gravity vector in the device co-ordinate\n
*						Set X, Y,Z-axis geomagnetic vector in the device co-ordinate\n
*						Create the array of 9 floats that represent rotation and inclination matrix
* @apicovered			sensor_util_get_rotation_matrix				
* @passcase				When sensor_util_get_rotation_matrix is successful
* @failcase				If target API sensor_util_get_rotation_matrix fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_rotation_matrix_p(void)
{
	START_TEST;

	float fGxAxis = 5.22;
	float fGyAxis = 0;
	float fGzAxis = 0;
	float fMxAxis = 0;
	float fMyAxis = 0;
	float fMzAXis = 12.22;
	float fRotation[9];
	float fInclination[9];

	// Target API
	int nRet = sensor_util_get_rotation_matrix(fGxAxis, fGyAxis, fGzAxis, fMxAxis, fMyAxis, fMzAXis, fRotation, fInclination);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_rotation_matrix", SensorsGetError(nRet));

	return 0;
}

//& purpose: To convert a rotation vector to a rotation matrix. 
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_rotation_matrix_from_vector_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To convert a rotation vector to a rotation matrix
* @scenario				Set X,Y,Z-axis rotation vector\n
*						Set 9 elements array rotation matrix 
* @apicovered			sensor_util_get_rotation_matrix_from_vector				
* @passcase				When sensor_util_get_rotation_matrix_from_vector is successful
* @failcase				If target API sensor_util_get_rotation_matrix_from_vector fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_rotation_matrix_from_vector_p(void)
{
	START_TEST;

	float fVxAxis = 5;
	float fVyAxis = 12.24;
	float fVzAxis = 13.26;
	float fRotation[9];

	// Target API
	int nRet = sensor_util_get_rotation_matrix_from_vector(fVxAxis, fVyAxis, fVzAxis, fRotation);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_rotation_matrix_from_vector", SensorsGetError(nRet));

	return 0;
}

//& purpose: Gets the altitude from the atmospheric pressure, the pressure at sea level and temperature, in meters.
//& type: auto
/**
* @testcase ITc_sensor_util_get_altitude_p
* @type auto
* @author SRID(priya.kohli)
* @reviewer SRID(shobhit.v)
* @since_tizen 4.0
* @description Gets the altitude from the atmospheric pressure, the pressure at sealevel and temperature, in meters.
* @apicovered sensor_util_get_altitude
* @passcase When sensor_util_get_altitudem is successful
* @failcase If target API sensor_util_get_altitude fails or any precondition API fails
* @precondition NA
* @postcondition NA
*/
int ITc_sensor_util_get_altitude_p(void)
{
	START_TEST;

	int nRet = SENSOR_ERROR_NONE;
	float fPressure = 1000.0;
	float fSeaLvlPres = 1013.25; /* Standard sea level pressure */
	float fTemperature = 15;
	float fAltitude=0.0;

	nRet = sensor_util_get_altitude(fPressure, fSeaLvlPres, fTemperature, &fAltitude);
	PRINT_RESULT(nRet, SENSOR_ERROR_NONE, "sensor_util_get_altitude", SensorsGetError(nRet));
	if(fAltitude < 0.0)
	{
		FPRINTF("[Line : %d][%s] nAltitude value is less then 0.0, value returned: %f \\n",__LINE__, API_NAMESPACE, fAltitude);
		return 1;
	}
	FPRINTF("[Line : %d][%s] value returned: %f \\n", __LINE__, API_NAMESPACE, fAltitude);
	return 0;
}

//& purpose: To rotate the supplied rotation matrix so that it can be expressed in a different coordinate system
//& type: auto
/**
* @testcase 			ITc_sensor_util_remap_coordinate_system_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To rotate the supplied rotation matrix so that it can be expressed in a different coordinate system.
* @scenario				Set the rotation matrix(3x3) which is to be transformed\n
*						Set x and y axis of the device\n
*						Set the transformed rotation matrix 
* @apicovered			sensor_util_remap_coordinate_system				
* @passcase				When sensor_util_remap_coordinate_system is successful
* @failcase				If target API sensor_util_remap_coordinate_system fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_remap_coordinate_system_p(void)
{
	START_TEST;

	float fInR[9] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};
	float fOutR[9] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
	sensor_util_axis_e eSensorUtilAxisX = sensor_util_axis_x;
	sensor_util_axis_e eSensorUtilAxisY = sensor_util_axis_minus_y;
	int i;

	// Target API
	int nRet = sensor_util_remap_coordinate_system(fInR, eSensorUtilAxisX, eSensorUtilAxisY, fOutR);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_remap_coordinate_system", SensorsGetError(nRet));
	for(i=0;i<9;i++)
	{
		if (i%3 != 1)
			continue;

		if (fOutR[i] >= 0.0f)
		{
			FPRINTF("[Line : %d][%s] sensor_util_remap_coordinate_system failed, invalid output value for i = %d is %f\\n", __LINE__, API_NAMESPACE,i,fOutR[i]);
			return 1;
		}
	}

	return 0;
}

//& purpose: To compute the geomagnetic inclination angle in radians from the inclination matrix
//& type: auto
/**
* @testcase 			ITc_sensor_util_get_inclination_p
* @type 				auto
* @author				SRID(gupta.sanjay)
* @reviewer				SRID(ravi.kumar2)
* @since_tizen 			2.3
* @description			To compute the geomagnetic inclination angle in radians from the inclination matrix 
* @scenario				Set the inclination matrix\n
*						Get the inclination angle in radians
* @apicovered			sensor_util_get_inclination				
* @passcase				When sensor_util_get_inclination is successful
* @failcase				If target API sensor_util_get_inclination fails or any precondition API fails
* @precondition			Sensor handle must be created
* @postcondition		NA
*/
int ITc_sensor_util_get_inclination_p(void)
{
	START_TEST;

	float fI[] = {1, 1, 1, 1, 1, 1, 1, 1, 1};
	float fInclination = -1.0;

	// Target API
	int nRet = sensor_util_get_inclination(fI, &fInclination);
	PRINT_RESULT(SENSOR_ERROR_NONE, nRet, "sensor_util_get_inclination", SensorsGetError(nRet));
	if(fInclination == -1.0)
	{
		FPRINTF("[Line : %d][%s] sensor_util_get_inclination failed, output value is invalid\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}
/** @} */ 
/** @} */ 
