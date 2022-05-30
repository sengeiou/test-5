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
* @function			GetDataFromFile
* @description		Called to get data
* @parameter		NA
* @return			NA
*/
unsigned int GetDataFromFile()
{
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	if ( true == GetValueForTCTSetting("DEVICE_SUITE_TARGET_30", pszValue, API_NAMESPACE ))
	{
			FPRINTF("[Line : %d][%s] 'DEVICE_SUITE_TARGET_30' Values Received = %s\\n", __LINE__, API_NAMESPACE,  pszValue);
			int path_size = strlen(pszValue)+strlen("/res/movie.mp4")+1;
			g_pszFilePath=(char*)calloc(path_size, sizeof(char));
			if( NULL == g_pszFilePath )
			{
					FPRINTF("[Line : %d][%s] 'Memory allocation to g_pszFilePath failed\\n", __LINE__, API_NAMESPACE);
					return 1;
			}
			snprintf(g_pszFilePath, path_size, "%s/res/movie.mp4", pszValue);
			FPRINTF("[Line : %d][%s] g_pszFilePath = %s\\n", __LINE__, API_NAMESPACE,  g_pszFilePath);
	}
	else
	{
			FPRINTF("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
			return 1;
	}
	return 0;
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
