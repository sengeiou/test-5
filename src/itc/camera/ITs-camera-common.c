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
#include "ITs-camera-common.h"

/** @addtogroup itc-camera
*  @ingroup itc
*  @{
*/

/**
* @function 		CameraGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* CameraGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CAMERA_ERROR_INVALID_PARAMETER:			szErrorVal = "CAMERA_ERROR_INVALID_PARAMETER";			break;
	case CAMERA_ERROR_OUT_OF_MEMORY:				szErrorVal = "CAMERA_ERROR_OUT_OF_MEMORY";				break;
	case CAMERA_ERROR_INVALID_OPERATION:			szErrorVal = "CAMERA_ERROR_INVALID_OPERATION";			break;
	case CAMERA_ERROR_INVALID_STATE:				szErrorVal = "CAMERA_ERROR_INVALID_STATE";				break;
	case CAMERA_ERROR_DEVICE:						szErrorVal = "CAMERA_ERROR_DEVICE";						break;
	case CAMERA_ERROR_SECURITY_RESTRICTED:			szErrorVal = "CAMERA_ERROR_SECURITY_RESTRICTED";		break;
	case CAMERA_ERROR_DEVICE_BUSY:					szErrorVal = "CAMERA_ERROR_DEVICE_BUSY";				break;
	case CAMERA_ERROR_DEVICE_NOT_FOUND:				szErrorVal = "CAMERA_ERROR_DEVICE_NOT_FOUND";			break;
	case CAMERA_ERROR_ESD:							szErrorVal = "CAMERA_ERROR_ESD";						break;
	case CAMERA_ERROR_NOT_SUPPORTED:				szErrorVal = "CAMERA_ERROR_NOT_SUPPORTED";				break;
	case CAMERA_ERROR_RESOURCE_CONFLICT:			szErrorVal = "CAMERA_ERROR_RESOURCE_CONFLICT";			break;
	case CAMERA_ERROR_SERVICE_DISCONNECTED:			szErrorVal = "CAMERA_ERROR_SERVICE_DISCONNECTED";		break;
	default:										szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}
/** @} */

