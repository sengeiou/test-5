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
#include "CTs-sensor-common.h"

/** @addtogroup ctc-sensor
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 			SensorApiErrorInfo
* @description 			Get details error message
* @parameter	[IN]	nRet [API return Code]
* 				[IN]	pszApi	[the name of API for which error code is to be checked] 
* @return 				NA 
*/
void SensorApiErrorInfo(char *pszApi,int nRet)
{	
	char *pszErrMSG=NULL;
	switch ( nRet )
	{		
	case SENSOR_ERROR_IO_ERROR  : 					pszErrMSG = "SENSOR_ERROR_IO_ERROR";				break;
	case SENSOR_ERROR_INVALID_PARAMETER   :			pszErrMSG = "SENSOR_ERROR_INVALID_PARAMETER";		break;
	case SENSOR_ERROR_OUT_OF_MEMORY :				pszErrMSG = "SENSOR_ERROR_OUT_OF_MEMORY";			break;
	case SENSOR_ERROR_NOT_NEED_CALIBRATION :		pszErrMSG = "SENSOR_ERROR_NOT_NEED_CALIBRATION";	break;
	case SENSOR_ERROR_NOT_SUPPORTED:				pszErrMSG = "SENSOR_ERROR_NOT_SUPPORTED";			break;
	case SENSOR_ERROR_OPERATION_FAILED :			pszErrMSG = "SENSOR_ERROR_OPERATION_FAILED";		break;
	case SENSOR_ERROR_PERMISSION_DENIED  :			pszErrMSG = "SENSOR_ERROR_PERMISSION_DENIED";		break;
	default:										pszErrMSG = "UNKNOWN";
	}

	FPRINTF("[Line : %d][%s] %s is failed, error returned = %s (%d)\\n", __LINE__, API_NAMESPACE, pszApi, pszErrMSG, nRet);	
}

/**
* @function 		SensorCreate
* @description 		check if sensor is supported and create sensor
* @parameter		NA
* @return 			True if sensor is  created otherwise return false. 
*/
bool SensorCreate()
{
	int nRet = SENSOR_ERROR_NONE;

	nRet = sensor_create_listener(g_hSensor,&g_listener);
	if ( nRet != SENSOR_ERROR_NONE )
	{
		SensorApiErrorInfo("sensor_create_listener", nRet);
		return false;
	}	

	if ( g_listener == NULL )
	{
		FPRINTF("[Line : %d][%s] sensor_create_listener return Null listener\\n", __LINE__, API_NAMESPACE);	
		return false;
	}
	return true;
}

/**
* @function 			SensorCheckSupport
* @description 			check if sensor is supported 
* @parameter	[IN]	eSensorType 
* @return 				True if sensor is supported  otherwise return false. 
*/
bool SensorCheckSupport(sensor_type_e eSensorType)
{
	int nRet = SENSOR_ERROR_NONE;
	bool bIsSupported =false;
	nRet = sensor_is_supported(eSensorType, &bIsSupported);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_is_supported", nRet);
		return false;
	}

	if ( !bIsSupported )
	{
		FPRINTF("[Line : %d][%s] Sensor is not supported\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return true;
}

/**
* @function 			SensorGetDefaultSensor
* @description 			Gets a specific sensor handle. 
* @parameter	[IN]	eSensorType 
* @return 				True if gets a specific sensor handle otherwise return false. 
*/
bool SensorGetDefaultSensor(sensor_type_e eSensorType)
{
	int nRet = SENSOR_ERROR_NONE;

	nRet = sensor_get_default_sensor(eSensorType, &g_hSensor);
	if ( nRet != SENSOR_ERROR_NONE )
	{  
		SensorApiErrorInfo("sensor_get_default_sensor", nRet);
		return false;
	}

	if ( g_hSensor == NULL )
	{
		FPRINTF("[Line : %d][%s] sensor_get_default_sensor  return Null handle\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	return true;
}

/**
* @function 			SensorIsStart
* @description 			start sensor
* @parameter	[IN]	NA
* @return 				True if sensor is started otherwise return false.
*/
bool SensorIsStart()
{
	int nRet = SENSOR_ERROR_NONE;

	nRet = sensor_listener_start(g_listener);
	if ( nRet != SENSOR_ERROR_NONE )
	{   
		SensorApiErrorInfo("sensor_listener_start", nRet);
		return false;
	}	
	return true;
}

/**
* @function 			SensorUnsetcb
* @description 			Unregisters the  callback function
* @parameter	[IN]	NA
* @return 				True if Unregisters the  callback function otherwise return false.
*/
bool SensorUnsetcb()
{
	int nRet = SENSOR_ERROR_NONE;

	nRet = sensor_listener_unset_event_cb(g_listener);
	if ( nRet != SENSOR_ERROR_NONE )
	{
		SensorApiErrorInfo("sensor_listener_unset_event_cb", nRet);	
		return false;
	}	
	return true;
}

/**
* @function 			SensorStop
* @description 			stop and destroy sensor
* @parameter	[IN]	NA
* @return 				True if sensor is stop  properly otherwise return false.
*/
bool SensorStop()
{
	int nRet = SENSOR_ERROR_NONE;
	nRet = sensor_listener_stop(g_listener);

	if ( nRet != SENSOR_ERROR_NONE )
	{
		SensorApiErrorInfo("sensor_listener_stop", nRet);
		return false;
	}
	return true;
}

/**
* @function 			SensorDestroy
* @description 			Destroy sensor
* @parameter	[IN]	NA
* @return 				True if sensor is  destroyed properly otherwise return false.  
*/
bool SensorDestroy()
{
	int nRet = SENSOR_ERROR_NONE;

	nRet = sensor_destroy_listener(g_listener);
	if ( nRet != SENSOR_ERROR_NONE )
	{
		SensorApiErrorInfo("sensor_destroy_listener", nRet);
		return false;
	}		
	return true;
}

/** @} */ //end of ctc-sensor