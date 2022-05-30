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
#include "ITs-capi-mediademuxer-common.h"

/** @addtogroup itc-mediademuxer
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		MediademuxerGetState
* @description	 	Maps mediademuxer_state enums
* @parameter		state : state level
* @return 			state level string
*/
char* MediademuxerGetState(mediademuxer_state state)
{
	char *szStateVal = NULL;
	switch ( state )
	{
	case MEDIADEMUXER_STATE_NONE:			szStateVal = "MEDIADEMUXER_STATE_NONE";			break;
	case MEDIADEMUXER_STATE_IDLE:			szStateVal = "MEDIADEMUXER_STATE_IDLE";			break;
	case MEDIADEMUXER_STATE_READY:		szStateVal = "MEDIADEMUXER_STATE_READY";			break;
	case MEDIADEMUXER_STATE_DEMUXING:		szStateVal = "MEDIADEMUXER_STATE_DEMUXING";		break;
	}
	return szStateVal;
}

/**
* @function 		MediademuxerGetError
* @description	 	Maps mediademuxer_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* MediademuxerGetError(mediademuxer_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
	case MEDIADEMUXER_ERROR_NONE:					szErrorVal = "MEDIADEMUXER_ERROR_NONE";						break;
	case MEDIADEMUXER_ERROR_OUT_OF_MEMORY:			szErrorVal = "MEDIADEMUXER_ERROR_OUT_OF_MEMORY";			break;
	case MEDIADEMUXER_ERROR_INVALID_PARAMETER:		szErrorVal = "MEDIADEMUXER_ERROR_INVALID_PARAMETER";		break;
	case MEDIADEMUXER_ERROR_INVALID_OPERATION:		szErrorVal = "MEDIADEMUXER_ERROR_INVALID_OPERATION";		break;
	case MEDIADEMUXER_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIADEMUXER_ERROR_NOT_SUPPORTED";			break;
	case MEDIADEMUXER_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIADEMUXER_ERROR_PERMISSION_DENIED";		break;
	case MEDIADEMUXER_ERROR_INVALID_STATE:			szErrorVal = "MEDIADEMUXER_ERROR_INVALID_STATE";			break;
	case MEDIADEMUXER_ERROR_INVALID_PATH:			szErrorVal = "MEDIADEMUXER_ERROR_INVALID_PATH";				break;
	case MEDIADEMUXER_ERROR_RESOURCE_LIMIT:			szErrorVal = "MEDIADEMUXER_ERROR_RESOURCE_LIMIT";			break;
	case MEDIADEMUXER_ERROR_SEEK_FAILED:			szErrorVal = "MEDIADEMUXER_ERROR_SEEK_FAILED";				break;
	case MEDIADEMUXER_ERROR_DRM_NOT_PERMITTED:		szErrorVal = "MEDIADEMUXER_ERROR_DRM_NOT_PERMITTED";		break;
	default:										szErrorVal = "Unknown Error";								break;
	}

	return szErrorVal;
}
/** @} */
