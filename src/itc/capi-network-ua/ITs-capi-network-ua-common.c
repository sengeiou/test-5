//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-ua-common.h"

//Add helper function definitions here

/** @addtogroup itc-capi-network-ua
*  @ingroup itc
*  @{
*/
/**
* @function 		UaCallbackTimeout
* @description	 	callback function to terminate g_main loop
* @parameter		data : user data sent to callback
* @return 			NA
*/
gboolean UaCallbackTimeout(gpointer data)
{
	GMainLoop* pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	return false;
}

/**
* @function		UaGetError
* @description		Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* UaGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet)
	{
		case UA_ERROR_NONE:    szErrorVal = "UA_ERROR_NONE";    break;
		case UA_ERROR_NOT_PERMITTED:    szErrorVal = "UA_ERROR_NOT_PERMITTED";    break;
		case UA_ERROR_INVALID_PARAMETER:    szErrorVal = "UA_ERROR_INVALID_PARAMETER";    break;
		case UA_ERROR_OUT_OF_MEMORY:    szErrorVal = "UA_ERROR_OUT_OF_MEMORY";    break;
		case UA_ERROR_PERMISSION_DENIED:    szErrorVal = "UA_ERROR_PERMISSION_DENIED";    break;
		case UA_ERROR_RESOURCE_BUSY:    szErrorVal = "UA_ERROR_RESOURCE_BUSY";    break;
		case UA_ERROR_TIMED_OUT:    szErrorVal = "UA_ERROR_TIMED_OUT";    break;
		case UA_ERROR_CANCELED:    szErrorVal = "UA_ERROR_CANCELED";    break;
		case UA_ERROR_NOW_IN_PROGRESS:    szErrorVal = "UA_ERROR_NOW_IN_PROGRESS";    break;
		case UA_ERROR_NOT_SUPPORTED:    szErrorVal = "UA_ERROR_NOT_SUPPORTED";    break;
		case UA_ERROR_NO_DATA:    szErrorVal = "UA_ERROR_NO_DATA";    break;
		case UA_ERROR_NOT_INITIALIZED:    szErrorVal = "UA_ERROR_NOT_INITIALIZED";    break;
		case UA_ERROR_NOT_IN_PROGRESS:    szErrorVal = "UA_ERROR_NOT_IN_PROGRESS";    break;
		case UA_ERROR_ALREADY_DONE:    szErrorVal = "UA_ERROR_ALREADY_DONE";    break;
		case UA_ERROR_OPERATION_FAILED:    szErrorVal = "UA_ERROR_OPERATION_FAILED";    break;
		case UA_ERROR_NOT_READY:    szErrorVal = "UA_ERROR_NOT_READY";    break;
		case UA_ERROR_NOT_ENABLED:    szErrorVal = "UA_ERROR_NOT_ENABLED";    break;
		case UA_ERROR_NOT_FOUND:    szErrorVal = "UA_ERROR_NOT_FOUND";    break;
		case UA_ERROR_ALREADY_REGISTERED:    szErrorVal = "UA_ERROR_ALREADY_REGISTERED";    break;
		case UA_ERROR_DB_FAILED:    szErrorVal = "UA_ERROR_DB_FAILED";    break;
		case UA_ERROR_NOT_REGISTERED:     szErrorVal = "UA_ERROR_NOT_REGISTERED";    break;
		default:    szErrorVal = "UA_ERROR_UNKNOWN";    break;
	}

	return szErrorVal;
}
/**
* @function		UaGetEnumSensorString
* @description		Maps sensor type enums to string values
* @parameter		nVal : sensor type enum value
* @return			sensor type string
*/
char* UaGetEnumSensorString(int nVal)
{
	char *szString = NULL;
	switch ( nVal)
	{
		case UA_SENSOR_BT:    szString = "UA_SENSOR_BT";    break;
		case UA_SENSOR_BLE:    szString = "UA_SENSOR_BLE";    break;
		case UA_SENSOR_WIFI:    szString = "UA_SENSOR_WIFI";    break;
		case UA_SENSOR_MOTION:    szString = "UA_SENSOR_MOTION";    break;
		case UA_SENSOR_LIGHT:    szString = "UA_SENSOR_LIGHT";    break;
		case UA_SENSOR_AUDIO:    szString = "UA_SENSOR_AUDIO";    break;
		case UA_SENSOR_MAX:    szString = "UA_SENSOR_MAX";    break;
		default:    szString = "UA_SENSOR_ALL";    break;
	}

	return szString;
}
/**
* @function		UaGetEnumMacTypeString
* @description		Maps mac type enums to string values
* @parameter		nVal : mac type enum value
* @return			mac type string
*/
char* UaGetEnumMacTypeString(int nVal)
{
	char *szString = NULL;
	switch ( nVal)
	{
		case UA_MAC_TYPE_NONE:    szString = "UA_MAC_TYPE_NONE";    break;
		case UA_MAC_TYPE_BT:    szString = "UA_MAC_TYPE_BT";    break;
		case UA_MAC_TYPE_BLE:    szString = "UA_MAC_TYPE_BLE";    break;
		case UA_MAC_TYPE_WIFI:    szString = "UA_MAC_TYPE_WIFI";    break;
		case UA_MAC_TYPE_P2P:    szString = "UA_MAC_TYPE_P2P";    break;
		default:    szString = "UA_MAC_TYPE_INVALID";    break;
	}
	return szString;
}
/**
* @function		UaGetDetectionModeString
* @description		Maps detection mode enums to string values
* @parameter		nVal : detection mode enum value
* @return			detection mode string
*/
char* UaGetDetectionModeString(int nVal)
{
	char *szString = NULL;
	switch ( nVal)
	{
		case UA_DETECT_MODE_ALL_SENSORS:    szString = "UA_DETECT_MODE_ALL_SENSORS";    break;
		case UA_DETECT_MODE_ANY_SENSOR:    szString = "UA_DETECT_MODE_ANY_SENSOR";    break;
		default:    szString = "UA_DETECT_MODE_INVALID";    break;
	}
	return szString;
}
/** @} */
