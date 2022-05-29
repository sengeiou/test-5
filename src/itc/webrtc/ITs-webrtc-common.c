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
#include "ITs-webrtc-common.h"

/** @addtogroup itc-webrtc
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		WebRtcGetError
* @description	 	Maps webrtc_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* WebRtcGetError(int nErrorType)
{
	char *szErrorVal = "Unknown Error";
	switch ( nErrorType )
	{
		case WEBRTC_ERROR_NONE:					szErrorVal = "WEBRTC_ERROR_NONE";						break;
		case WEBRTC_ERROR_NOT_SUPPORTED:		szErrorVal = "WEBRTC_ERROR_NOT_SUPPORTED";				break;
		case WEBRTC_ERROR_PERMISSION_DENIED:	szErrorVal = "WEBRTC_ERROR_PERMISSION_DENIED";			break;
		case WEBRTC_ERROR_INVALID_PARAMETER:	szErrorVal = "WEBRTC_ERROR_INVALID_PARAMETER";			break;
		case WEBRTC_ERROR_INVALID_OPERATION:	szErrorVal = "WEBRTC_ERROR_INVALID_OPERATION";			break;
		case WEBRTC_ERROR_INVALID_STATE:		szErrorVal = "WEBRTC_ERROR_INVALID_STATE";				break;
		case WEBRTC_ERROR_CONNECTION_FAILED:	szErrorVal = "WEBRTC_ERROR_CONNECTION_FAILED";			break;
		case WEBRTC_ERROR_STREAM_FAILED:		szErrorVal = "WEBRTC_ERROR_STREAM_FAILED";				break;
		case WEBRTC_ERROR_RESOURCE_FAILED:		szErrorVal = "WEBRTC_ERROR_RESOURCE_FAILED";			break;
		case WEBRTC_ERROR_RESOURCE_CONFLICT:	szErrorVal = "WEBRTC_ERROR_RESOURCE_CONFLICT";			break;
	}

	return szErrorVal;
}

/**
* @function 		Timeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean Timeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}
/** @} */
