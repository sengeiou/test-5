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
#include "ITs-radio-common.h"

/** @addtogroup itc-radio
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		RadioGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* RadioGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case RADIO_ERROR_NONE:				szErrorVal = "RADIO_ERROR_NONE";					break;
	case RADIO_ERROR_INVALID_PARAMETER:	szErrorVal = "RADIO_ERROR_INVALID_PARAMETER";		break;
	case RADIO_ERROR_INVALID_OPERATION:	szErrorVal = "RADIO_ERROR_INVALID_OPERATION";		break;
	case RADIO_ERROR_OUT_OF_MEMORY:		szErrorVal = "RADIO_ERROR_OUT_OF_MEMORY";			break;
	case RADIO_ERROR_INVALID_STATE:		szErrorVal = "RADIO_ERROR_INVALID_STATE";			break;
	case RADIO_ERROR_SOUND_POLICY:		szErrorVal = "RADIO_ERROR_SOUND_POLICY";			break;
	default:							szErrorVal = "Unknown Error";						break;
	}

	return szErrorVal;
}

/**
* @function 		RadioGetState
* @description	 	Maps state enums to string values
* @parameter		nRet : state code returned
* @return 			state string
*/
char* RadioGetState(radio_state_e nRet)
{
	char *szStateVal = "Unknown State";
	switch ( nRet )
	{
	case RADIO_STATE_READY:			szStateVal = "RADIO_STATE_READY";			break;  
	case RADIO_STATE_PLAYING: 		szStateVal = "RADIO_STATE_PLAYING";			break;
	case RADIO_STATE_SCANNING:		szStateVal = "RADIO_STATE_SCANNING";		break;
	}

	return szStateVal;
}
/** @} */