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
#include "ITs-capi-ui-gesture-common.h"

/** @addtogroup itc-capi-ui-gesture
*  @ingroup itc
*  @{
*/

//Add helper function definitions here
/**
* @function 		GestureGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 		error string
*/
char* GestureGetError(int nRet)
{
	char *szErrorVal = "Unknown error code";
	switch ( nRet )
	{
		case HAND_GESTURE_ERROR_NONE:			szErrorVal = "HAND_GESTURE_ERROR_NONE";			break;
		case HAND_GESTURE_ERROR_INVALID_PARAMETER:	szErrorVal = "HAND_GESTURE_ERROR_INVALID_PARAMETER";			break;
		case HAND_GESTURE_ERROR_INVALID_OPERATION:	szErrorVal = "HAND_GESTURE_ERROR_INVALID_OPERATION";			break;
		case HAND_GESTURE_ERROR_OUT_OF_MEMORY:		szErrorVal = "HAND_GESTURE_ERROR_OUT_OF_MEMORY";			break;
		case HAND_GESTURE_ERROR_PERMISSION_DENIED:	szErrorVal = "HAND_GESTURE_ERROR_PERMISSION_DENIED";			break;
		case HAND_GESTURE_ERROR_NOT_SUPPORTED:		szErrorVal = "HAND_GESTURE_ERROR_NOT_SUPPORTED";			break;
		case HAND_GESTURE_ERROR_ALREADY_STARTED:	szErrorVal = "HAND_GESTURE_ERROR_ALREADY_STARTED";			break;
		case HAND_GESTURE_ERROR_NOT_STARTED:		szErrorVal = "HAND_GESTURE_ERROR_NOT_STARTED";			break;
		case HAND_GESTURE_ERROR_OPERATION_FAILED:	szErrorVal = "HAND_GESTURE_ERROR_OPERATION_FAILED";			break;
	}

	return szErrorVal;
}

/** @} */
