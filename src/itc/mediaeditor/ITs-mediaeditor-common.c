//
// Copyright (c) 2022 Samsung Electronics Co., Ltd.
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
#include "ITs-mediaeditor-common.h"

/** @addtogroup itc-mediaeditor
*  @ingroup itc
*  @{
*/

/**
* @function 		MEDIAEDITORGetError
* @description	 	Maps MEDIAEDITOR_error_e enums
* @parameter		error : error level
* @return 			error string
*/
char* MediaEditorGetError(int nErrorType)
{
	char *szErrorVal = "Unknown Error";
	switch (nErrorType)
	{
	case MEDIAEDITOR_ERROR_NONE:				szErrorVal = "MEDIAEDITOR_ERROR_NONE";						break;
	case MEDIAEDITOR_ERROR_NOT_SUPPORTED:		szErrorVal = "MEDIAEDITOR_ERROR_NOT_SUPPORTED";				break;
	case MEDIAEDITOR_ERROR_PERMISSION_DENIED:	szErrorVal = "MEDIAEDITOR_ERROR_PERMISSION_DENIED";			break;
	case MEDIAEDITOR_ERROR_INVALID_PARAMETER:	szErrorVal = "MEDIAEDITOR_ERROR_INVALID_PARAMETER";			break;
	case MEDIAEDITOR_ERROR_INVALID_OPERATION:	szErrorVal = "MEDIAEDITOR_ERROR_INVALID_OPERATION";			break;
	case MEDIAEDITOR_ERROR_INVALID_STATE:		szErrorVal = "MEDIAEDITOR_ERROR_INVALID_STATE";				break;
	case MEDIAEDITOR_ERROR_RESOURCE_FAILED:		szErrorVal = "MEDIAEDITOR_ERROR_RESOURCE_FAILED";			break;
	case MEDIAEDITOR_ERROR_RESOURCE_CONFLICT:	szErrorVal = "MEDIAEDITOR_ERROR_RESOURCE_CONFLICT";			break;
	}

	return szErrorVal;
}

/**
* @function 		MediaStreamerGetState
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MediaEditorGetState(int nRet)
{
	char *szState = NULL;
	switch (nRet)
	{
	case MEDIAEDITOR_STATE_IDLE:						szState = "MEDIAEDITOR_STATE_IDLE";					break;
	case MEDIAEDITOR_STATE_RENDERING:					szState = "MEDIAEDITOR_STATE_RENDERING";			break;
	case MEDIAEDITOR_STATE_PREVIEW:						szState = "MEDIAEDITOR_STATE_PREVIEW";				break;
	default:											szState = "Unknown Error";							break;
	}
	return szState;
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
	if (pMainLoop != NULL)
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}


/** @} */
