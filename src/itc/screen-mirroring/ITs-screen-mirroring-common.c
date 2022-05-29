//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an"AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include"ITs-screen-mirroring-common.h"

/** @addtogroup itc-screen-mirroring
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		ScreenMirroringInfoGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ScreenMirroringInfoGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case SCMIRRORING_ERROR_NONE:
		szErrorVal = "SCMIRRORING_ERROR_NONE";
		break;
	case SCMIRRORING_ERROR_INVALID_PARAMETER:
		szErrorVal = "SCMIRRORING_ERROR_INVALID_PARAMETER";
		break;
	case SCMIRRORING_ERROR_INVALID_OPERATION:
		szErrorVal = "SCMIRRORING_ERROR_INVALID_OPERATION";
		break;
	case SCMIRRORING_ERROR_OUT_OF_MEMORY:
		szErrorVal = "SCMIRRORING_ERROR_OUT_OF_MEMORY";
		break;
	case SCMIRRORING_ERROR_CONNECTION_TIME_OUT:
		szErrorVal = "SCMIRRORING_ERROR_CONNECTION_TIME_OUT";
		break;
	case SCMIRRORING_ERROR_PERMISSION_DENIED:
		szErrorVal = "SCMIRRORING_ERROR_PERMISSION_DENIED";
		break;
	default:
		szErrorVal = "Unknown Error";
		break;
	}

	return szErrorVal;
}

/**
* @function 		ScreenMirroringInfoDisplayType
* @description	 	Maps scmirroring_display_type_e to string values
* @parameter		nRet : scmirroring_display_type_e code returned
* @return 			scmirroring_display_type_e string
*/
char* ScreenMirroringInfoDisplayType(scmirroring_display_type_e nRet)
{
	char *szGrantVal = NULL;

	switch ( nRet )
	{
	case SCMIRRORING_DISPLAY_TYPE_OVERLAY:
		szGrantVal = "SCMIRRORING_DISPLAY_TYPE_OVERLAY";
		break;
	case SCMIRRORING_DISPLAY_TYPE_EVAS:
		szGrantVal = "SCMIRRORING_DISPLAY_TYPE_EVAS";
		break;
	default:
		break;
	}

	return szGrantVal;
}

/**
* @function 		ScreenMirroringInfoResolution
* @description	 	Maps scmirroring_resolution_e to string values
* @parameter		nRet : scmirroring_resolution_e code returned
* @return 			scmirroring_resolution_e string
*/
char* ScreenMirroringInfoResolution(scmirroring_resolution_e nRet)
{
	char *szGrantVal = NULL;

	switch ( nRet )
	{
	case SCMIRRORING_RESOLUTION_1920x1080_P30:
		szGrantVal = "SCMIRRORING_RESOLUTION_1920x1080_P30";
		break;
	case SCMIRRORING_RESOLUTION_1280x720_P30:
		szGrantVal = "SCMIRRORING_RESOLUTION_1280x720_P30";
		break;
	case SCMIRRORING_RESOLUTION_960x540_P30:
		szGrantVal = "SCMIRRORING_RESOLUTION_960x540_P30";
		break;
	case SCMIRRORING_RESOLUTION_864x480_P30:
		szGrantVal = "SCMIRRORING_RESOLUTION_864x480_P30";
		break;
	case SCMIRRORING_RESOLUTION_720x480_P60:
		szGrantVal = "SCMIRRORING_RESOLUTION_720x480_P60";
		break;
	case SCMIRRORING_RESOLUTION_640x480_P60:
		szGrantVal = "SCMIRRORING_RESOLUTION_640x480_P60";
		break;
	case SCMIRRORING_RESOLUTION_640x360_P30:
		szGrantVal = "SCMIRRORING_RESOLUTION_640x360_P30";
		break;
	default:
		break;
	}

	return szGrantVal;
}

/**
* @function 		ScreenMirroringSinkState
* @description	 	Maps scmirroring_sink_state_e to string values
* @parameter		nRet : scmirroring_sink_state_e code returned
* @return 			scmirroring_sink_state_e string
*/
char* ScreenMirroringSinkState(scmirroring_sink_state_e nRet)
{
	char *szStateVal = NULL;

	switch ( nRet )
	{
	case SCMIRRORING_SINK_STATE_NONE:
		szStateVal = "SCMIRRORING_SINK_STATE_NONE";
		break;
	case SCMIRRORING_SINK_STATE_NULL:
		szStateVal = "SCMIRRORING_SINK_STATE_NULL";
		break;
	case SCMIRRORING_SINK_STATE_PREPARED:
		szStateVal = "SCMIRRORING_SINK_STATE_PREPARED";
		break;
	case SCMIRRORING_SINK_STATE_CONNECTED:
		szStateVal = "SCMIRRORING_SINK_STATE_CONNECTED";
		break;
	case SCMIRRORING_SINK_STATE_PLAYING:
		szStateVal = "SCMIRRORING_SINK_STATE_PLAYING";
		break;
	case SCMIRRORING_SINK_STATE_PAUSED:
		szStateVal = "SCMIRRORING_SINK_STATE_PAUSED";
		break;
	case SCMIRRORING_SINK_STATE_DISCONNECTED:
		szStateVal = "SCMIRRORING_SINK_STATE_DISCONNECTED";
		break;
	case SCMIRRORING_SINK_STATE_MAX:
		szStateVal = "SCMIRRORING_SINK_STATE_MAX";
		break;
	}

	return szStateVal;
}
/** @} */