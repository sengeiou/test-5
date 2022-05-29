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
#include "CTs-device-common.h"

/** @addtogroup ctc-device
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 		DeviceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* DeviceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case DEVICE_ERROR_NONE:					szErrorVal = "DEVICE_ERROR_NONE";					break;
	case DEVICE_ERROR_OPERATION_FAILED:		szErrorVal = "DEVICE_ERROR_OPERATION_FAILED";		break;
	case DEVICE_ERROR_PERMISSION_DENIED:	szErrorVal = "DEVICE_ERROR_PERMISSION_DENIED";		break;
	case DEVICE_ERROR_INVALID_PARAMETER:	szErrorVal = "DEVICE_ERROR_INVALID_PARAMETER";		break;
	case DEVICE_ERROR_ALREADY_IN_PROGRESS:	szErrorVal = "DEVICE_ERROR_ALREADY_IN_PROGRESS";	break;
	case DEVICE_ERROR_NOT_SUPPORTED:		szErrorVal = "DEVICE_ERROR_NOT_SUPPORTED";			break;
	case DEVICE_ERROR_NOT_INITIALIZED:		szErrorVal = "DEVICE_ERROR_NOT_INITIALIZED";		break;
	default:								szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function 		DeviceGetLedFlag
* @description	 	Maps led enums to string values
* @parameter		nFlag : led flag value
* @return 			string to led flag value
*/
char* DeviceGetLedFlag(int nFlag)
{
	return ( nFlag == 0 ) ? "LED_CUSTOM_DUTY_ON" : "LED_CUSTOM_DEFAULT";
}

/** @} */ //end of ctc-device