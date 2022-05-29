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
#include "ITs-capi-media-streamer-common.h"

/** @addtogroup itc-capi-media-streamer
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		MediaStreamerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaStreamerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MEDIA_STREAMER_ERROR_NONE:						szErrorVal = "MEDIA_STREAMER_ERROR_NONE";					break;
	case MEDIA_STREAMER_ERROR_INVALID_PARAMETER:		szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_PARAMETER";		break;
	case MEDIA_STREAMER_ERROR_INVALID_OPERATION:		szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_OPERATION";		break;
	case MEDIA_STREAMER_ERROR_FILE_NO_SPACE_ON_DEVICE:	szErrorVal = "MEDIA_STREAMER_ERROR_FILE_NO_SPACE_ON_DEVICE";break;
	case MEDIA_STREAMER_ERROR_NOT_SUPPORTED:			szErrorVal = "MEDIA_STREAMER_ERROR_NOT_SUPPORTED";			break;
	case MEDIA_STREAMER_ERROR_PERMISSION_DENIED:		szErrorVal = "MEDIA_STREAMER_ERROR_PERMISSION_DENIED";		break;
	case MEDIA_STREAMER_ERROR_INVALID_STATE:			szErrorVal = "MEDIA_STREAMER_ERROR_INVALID_STATE";			break;
	case MEDIA_STREAMER_ERROR_CONNECTION_FAILED:		szErrorVal = "MEDIA_STREAMER_ERROR_CONNECTION_FAILED";		break;
	case MEDIA_STREAMER_ERROR_RESOURCE_CONFLICT:		szErrorVal = "MEDIA_STREAMER_ERROR_RESOURCE_CONFLICT";		break;
	case MEDIA_STREAMER_ERROR_SEEK_FAILED:				szErrorVal = "MEDIA_STREAMER_ERROR_SEEK_FAILED";			break;
	default:											szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}
/**
* @function 		MediaStreamerGetState
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaStreamerGetState(int nRet)
{
	char *szState = NULL;
	switch ( nRet )
	{
	case MEDIA_STREAMER_STATE_NONE:							szState = "MEDIA_STREAMER_STATE_NONE";					break;
	case MEDIA_STREAMER_STATE_IDLE:							szState = "MEDIA_STREAMER_STATE_IDLE";					break;
	case MEDIA_STREAMER_STATE_READY:						szState = "MEDIA_STREAMER_STATE_READY";					break;
	case MEDIA_STREAMER_STATE_PLAYING:						szState = "MEDIA_STREAMER_STATE_PLAYING";				break;
	case MEDIA_STREAMER_STATE_PAUSED:						szState = "MEDIA_STREAMER_STATE_PAUSED";				break;
	case MEDIA_STREAMER_STATE_SEEKING:						szState = "MEDIA_STREAMER_STATE_SEEKING";				break;
	default:												szState = "Unknown Error";								break;
	}
	return szState;
}

/**
* @function 		SystemInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SystemInfoGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case SYSTEM_INFO_ERROR_NONE :				szErrorVal = "SYSTEM_INFO_ERROR_NONE";					break; 
	case SYSTEM_INFO_ERROR_INVALID_PARAMETER :	szErrorVal = "SYSTEM_INFO_ERROR_INVALID_PARAMETER";		break; 
	case SYSTEM_INFO_ERROR_IO_ERROR :			szErrorVal = "SYSTEM_INFO_ERROR_IO_ERROR";				break;
	case SYSTEM_INFO_ERROR_OUT_OF_MEMORY :		szErrorVal = "SYSTEM_INFO_ERROR_OUT_OF_MEMORY";			break;
	case SYSTEM_INFO_ERROR_NOT_SUPPORTED :		szErrorVal = "SYSTEM_INFO_ERROR_NOT_SUPPORTED";			break;
	default :									szErrorVal = "Unknown error";							break;
	}
	return szErrorVal;
}

/**
* @function 		MediaStreamerTimeoutFunction
* @description	 	Called if some callback is not invoked for a Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean MediaStreamerTimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Callback MediaStreamer wait complete for 20 seconds. Timeout\\n",__LINE__, API_NAMESPACE);
	ecore_main_loop_quit();
	return FALSE;
}



/**
* @function 		MediaStreamerWaitForAsync
* @description	 	Called to wait callback function
* @parameter		NA
* @return 			NA
*/
void MediaStreamerWaitForAsync()
{
	g_timeout_add(TIMEOUT, MediaStreamerTimeoutFunction, NULL);
	ecore_main_loop_begin();
}

/** @} */