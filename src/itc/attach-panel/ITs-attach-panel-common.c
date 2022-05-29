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
#include "ITs-attach-panel-common.h"

/** @addtogroup itc-attach-panel
*  @ingroup itc
*  @{
*/

/**
* @function 		AttachPanelGetError
* @description	 	Maps attach_panel_error_e enums 
* @parameter		error : error level
* @return 			error string
*/
char* AttachPanelGetError(attach_panel_error_e error)
{
	char *szErrorVal = NULL;
	switch ( error )
	{
		case ATTACH_PANEL_ERROR_NONE:							szErrorVal = "ATTACH_PANEL_ERROR_NONE";							break;
		case ATTACH_PANEL_ERROR_INVALID_PARAMETER:				szErrorVal = "ATTACH_PANEL_ERROR_INVALID_PARAMETER";			break;
		case ATTACH_PANEL_ERROR_OUT_OF_MEMORY:					szErrorVal = "ATTACH_PANEL_ERROR_OUT_OF_MEMORY";				break;
		case ATTACH_PANEL_ERROR_PERMISSION_DENIED:				szErrorVal = "ATTACH_PANEL_ERROR_PERMISSION_DENIED";			break;
		case ATTACH_PANEL_ERROR_ALREADY_EXISTS:					szErrorVal = "ATTACH_PANEL_ERROR_ALREADY_EXISTS";				break;
		case  ATTACH_PANEL_ERROR_NOT_INITIALIZED:				szErrorVal = " ATTACH_PANEL_ERROR_NOT_INITIALIZED";				break;
		case ATTACH_PANEL_ERROR_UNSUPPORTED_CONTENT_CATEGORY:	szErrorVal = "ATTACH_PANEL_ERROR_UNSUPPORTED_CONTENT_CATEGORY";	break;
		case  ATTACH_PANEL_ERROR_ALREADY_DESTROYED:				szErrorVal = " ATTACH_PANEL_ERROR_ALREADY_DESTROYED";			break;
		case  ATTACH_PANEL_ERROR_NOT_SUPPORTED:					szErrorVal = " ATTACH_PANEL_ERROR_NOT_SUPPORTED";				break;
		default:												szErrorVal = "Unknown Error";									break;
	}
  
	return szErrorVal;
}
/** @} */
