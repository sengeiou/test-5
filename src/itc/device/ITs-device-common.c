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
#include "ITs-device-common.h"

/** @addtogroup itc-device
*  @ingroup itc
*  @{
*/

/**
* @function 		DeviceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* DeviceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch (nRet)
	{
	case DEVICE_ERROR_NONE:						szErrorVal = "DEVICE_ERROR_NONE";					break;
	case DEVICE_ERROR_OPERATION_FAILED:			szErrorVal = "DEVICE_ERROR_OPERATION_FAILED";		break;
	case DEVICE_ERROR_PERMISSION_DENIED:		szErrorVal = "DEVICE_ERROR_PERMISSION_DENIED";		break;
	case DEVICE_ERROR_INVALID_PARAMETER:		szErrorVal = "DEVICE_ERROR_INVALID_PARAMETER";		break;
	case DEVICE_ERROR_ALREADY_IN_PROGRESS:		szErrorVal = "DEVICE_ERROR_ALREADY_IN_PROGRESS";	break;
	case DEVICE_ERROR_NOT_SUPPORTED:			szErrorVal = "DEVICE_ERROR_NOT_SUPPORTED";			break;
	case DEVICE_ERROR_NOT_INITIALIZED:			szErrorVal = "DEVICE_ERROR_NOT_INITIALIZED";		break;
	default:									szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function 		DeviceGetCallbackType
* @description	 	Maps callback type to string values
* @parameter		type : callback type
* @return 			string value of callback type
*/
char* DeviceGetCallbackType(int type)
{
	char* szType = NULL;

	switch (type)
	{
	case DEVICE_CALLBACK_BATTERY_CAPACITY:		szType = "DEVICE_CALLBACK_BATTERY_CAPACITY";		break;
	case DEVICE_CALLBACK_BATTERY_LEVEL:			szType = "DEVICE_CALLBACK_BATTERY_LEVEL";			break;
	case DEVICE_CALLBACK_BATTERY_CHARGING:		szType = "DEVICE_CALLBACK_BATTERY_CHARGING";		break;
	case DEVICE_CALLBACK_DISPLAY_STATE:			szType = "DEVICE_CALLBACK_DISPLAY_STATE";			break;
	case DEVICE_CALLBACK_MAX:					szType = "DEVICE_CALLBACK_MAX";						break;
	default:									szType = "Unknown Type";							break;
	}

	return szType;
}

/**
* @function 		DeviceGetDisplayState
* @description	 	Maps display state to string values
* @parameter		state : display state
* @return 			string value of display state
*/
char* DeviceGetDisplayState(int state)
{
	char* szDisplayState = NULL;

	switch (state)
	{
	case DISPLAY_STATE_NORMAL:			szDisplayState = "DISPLAY_STATE_NORMAL";		break;
	case DISPLAY_STATE_SCREEN_DIM:		szDisplayState = "DISPLAY_STATE_SCREEN_DIM";	break;
	case DISPLAY_STATE_SCREEN_OFF:		szDisplayState = "DISPLAY_STATE_SCREEN_OFF";	break;
	default:							szDisplayState = "Unknown State";				break;
	}

	return szDisplayState;
}

/**
* @function 		DeviceGetLedFlag
* @description	 	Maps led flag value to string values
* @parameter		flag : led flag value
* @return 			string value of led flag value
*/
char* DeviceGetLedFlag(int flag)
{
	char* szFlag = NULL;

	if ( flag == LED_CUSTOM_DUTY_ON )
	{
		szFlag = "LED_CUSTOM_DUTY_ON";
	}
	else if ( flag == LED_CUSTOM_DEFAULT )
	{
		szFlag = "LED_CUSTOM_DEFAULT";
	}
	else
	{
		szFlag = "Unknown Flag";
	}

	return szFlag;
}

/**
* @function 		DeviceGetPowerLock
* @description	 	Maps power lock value to string values
* @parameter		flag : power lock value
* @return 			string value of power lock value
*/
char* DeviceGetPowerLock(int lock)
{
	char* szLock = NULL;

	switch (lock)
	{
	case POWER_LOCK_CPU:		szLock = "POWER_LOCK_CPU";			break;
	case POWER_LOCK_DISPLAY:	szLock = "POWER_LOCK_DISPLAY";		break;
	default:					szLock = "Unknown Lock";			break;
	}

	return szLock;
}
/** @} */
