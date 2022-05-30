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
#ifndef _ITS_CAPI_MEDIA_STREAMER_COMMON_H_
#define _ITS_CAPI_MEDIA_STREAMER_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <glib.h>
#include <string.h>
#include <Ecore.h>
#include <media/media_streamer.h>

media_format_h vfmt_encoded;
media_streamer_h streamer;
bool g_bMediaStreamerPositionChangedCallback;
#define VIDEO_WIDTH 1280
#define VIDEO_HEIGHT 720
#define VIDEO_FRAME_RATE 30
#define API_NAMESPACE	"CAPI_MEDIA_STREAMER_ITC"
#define USER_DATA_STR	"callback_user_data"
#define TIMEOUT 20000


#define START_TEST {\
	FPRINTF("\\n[Line : %d][%s] Starting test : %s\\n",__LINE__, API_NAMESPACE,__FUNCTION__);\
}



/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/

//Add helper function declarations here


/**
* @function 		MediaStreamerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaStreamerGetError(int nRet);



/**
* @function 		MediaStreamerGetState
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaStreamerGetState(int nRet);



/**
* @function 		MediaStreamerTimeoutFunction
* @description	 	Called if some callback is not invoked for a Timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean MediaStreamerTimeoutFunction(gpointer data);



/**
* @function 		MediaStreamerWaitForAsync
* @description	 	Called to wait callback function
* @parameter		NA
* @return 			NA
*/
void MediaStreamerWaitForAsync();

/**
* @function 		SystemInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SystemInfoGetError(int nRet);
/** @} */
#endif  //_ITS_CAPI_MEDIA_STREAMER_COMMON_H_
