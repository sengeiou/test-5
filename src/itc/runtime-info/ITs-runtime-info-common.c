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
#include "ITs-runtime-info-common.h"

/** @addtogroup itc-runtime-info
*  @ingroup itc
*  @{
*/

/**
* @function 		RuntimeInfoGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool RuntimeInfoGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF( "[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);
	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF( "[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pPath)+1);
	return true;
}

/**
* @function 		RuntimeInfoAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool RuntimeInfoAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( (NULL == pInputPath) || (NULL == pFinalPath) )
	{
		FPRINTF( "[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == RuntimeInfoGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, strlen(pAppDataPath)+1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);
	return true;
}

/**
* @function 		RuntimeInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* RuntimeInfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch(nRet)
	{
	case RUNTIME_INFO_ERROR_NONE:					szErrorVal = "RUNTIME_INFO_ERROR_NONE";						break;
	case RUNTIME_INFO_ERROR_INVALID_PARAMETER:		szErrorVal = "RUNTIME_INFO_ERROR_INVALID_PARAMETER";		break;
	case RUNTIME_INFO_ERROR_OUT_OF_MEMORY:			szErrorVal = "RUNTIME_INFO_ERROR_OUT_OF_MEMORY";			break;
	case RUNTIME_INFO_ERROR_IO_ERROR:				szErrorVal = "RUNTIME_INFO_ERROR_IO_ERROR";					break;
	case RUNTIME_INFO_ERROR_NO_DATA :				szErrorVal = "RUNTIME_INFO_ERROR_NO_DATA";					break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		RuntimeGetKeyString
* @description	 	Maps key type enums to string values
* @parameter		nRet : key type code returned
* @return 			key type string
*/
char* RuntimeGetKeyString(int nRet)
{
	char *szVal = NULL;
	switch ( nRet )
	{
	case RUNTIME_INFO_KEY_BLUETOOTH_ENABLED:					szVal = "RUNTIME_INFO_KEY_BLUETOOTH_ENABLED";						break;
	case RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED:					szVal = "RUNTIME_INFO_KEY_WIFI_HOTSPOT_ENABLED";					break;
	case RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED:			szVal = "RUNTIME_INFO_KEY_BLUETOOTH_TETHERING_ENABLED";				break;
	case RUNTIME_INFO_KEY_USB_TETHERING_ENABLED:				szVal = "RUNTIME_INFO_KEY_USB_TETHERING_ENABLED";					break;
	case RUNTIME_INFO_KEY_PACKET_DATA_ENABLED:					szVal = "RUNTIME_INFO_KEY_PACKET_DATA_ENABLED";						break;
	case RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED:					szVal = "RUNTIME_INFO_KEY_DATA_ROAMING_ENABLED";					break;
	case RUNTIME_INFO_KEY_VIBRATION_ENABLED:					szVal = "RUNTIME_INFO_KEY_VIBRATION_ENABLED";						break;
	case RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED:					szVal = "RUNTIME_INFO_KEY_AUDIO_JACK_CONNECTED";					break;
	case RUNTIME_INFO_KEY_GPS_STATUS:							szVal = "RUNTIME_INFO_KEY_GPS_STATUS";								break;
	case RUNTIME_INFO_KEY_BATTERY_IS_CHARGING:					szVal = "RUNTIME_INFO_KEY_BATTERY_IS_CHARGING";						break;
	case RUNTIME_INFO_KEY_TV_OUT_CONNECTED:						szVal = "RUNTIME_INFO_KEY_TV_OUT_CONNECTED";						break;
	case RUNTIME_INFO_KEY_AUDIO_JACK_STATUS:					szVal = "RUNTIME_INFO_KEY_AUDIO_JACK_STATUS";						break;
	case RUNTIME_INFO_KEY_USB_CONNECTED:						szVal = "RUNTIME_INFO_KEY_USB_CONNECTED";							break;
	case RUNTIME_INFO_KEY_CHARGER_CONNECTED:					szVal = "RUNTIME_INFO_KEY_CHARGER_CONNECTED";						break;
	case RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED:				szVal = "RUNTIME_INFO_KEY_AUTO_ROTATION_ENABLED";					break;
	default:													szVal = "Undefined Key";											break;
	}
	return szVal;
}
/** @} */
