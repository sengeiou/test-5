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
#include "ITs-eom-common.h"

/** @addtogroup itc-eom
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		EomGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EomGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case EOM_ERROR_NONE:						szErrorVal = "EOM_ERROR_NONE";							break;
	case EOM_ERROR_OUT_OF_MEMORY:				szErrorVal = "EOM_ERROR_OUT_OF_MEMORY";					break;
	case EOM_ERROR_INVALID_PARAMETER:			szErrorVal = "EOM_ERROR_INVALID_PARAMETER";				break;
	case EOM_ERROR_NO_SUCH_DEVICE:				szErrorVal = "EOM_ERROR_NO_SUCH_DEVICE";				break;
	case EOM_ERROR_CONNECTION_FAILURE:			szErrorVal = "EOM_ERROR_CONNECTION_FAILURE";			break;
	case EOM_ERROR_MESSAGE_SENDING_FAILURE:		szErrorVal = "EOM_ERROR_MESSAGE_SENDING_FAILURE";		break;
	case EOM_ERROR_MESSAGE_OPERATION_FAILURE:	szErrorVal = "EOM_ERROR_MESSAGE_OPERATION_FAILURE";		break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		EomGetExternalOutputType
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* EomGetExternalOutputType(int nType)
{
	char *szErrorVal = NULL;

	switch ( nType )
	{
	case EOM_OUTPUT_TYPE_UNKNOWN:				szErrorVal = "EOM_OUTPUT_TYPE_UNKNOWN";			break;
	case EOM_OUTPUT_TYPE_VGA:					szErrorVal = "EOM_OUTPUT_TYPE_VGA";				break;
	case EOM_OUTPUT_TYPE_DVII:					szErrorVal = "EOM_OUTPUT_TYPE_DVII";			break;
	case EOM_OUTPUT_TYPE_DVID:					szErrorVal = "EOM_OUTPUT_TYPE_DVID";			break;
	case EOM_OUTPUT_TYPE_DVIA:					szErrorVal = "EOM_OUTPUT_TYPE_DVIA";			break;
	case EOM_OUTPUT_TYPE_COMPOSITE:				szErrorVal = "EOM_OUTPUT_TYPE_COMPOSITE";		break;
	case EOM_OUTPUT_TYPE_SVIDEO:				szErrorVal = "EOM_OUTPUT_TYPE_SVIDEO";			break;
	case EOM_OUTPUT_TYPE_LVDS:					szErrorVal = "EOM_OUTPUT_TYPE_LVDS";			break;
	case EOM_OUTPUT_TYPE_COMPONENT:				szErrorVal = "EOM_OUTPUT_TYPE_COMPONENT";		break;
	case EOM_OUTPUT_TYPE_9PINDIN:				szErrorVal = "EOM_OUTPUT_TYPE_9PINDIN";			break;
	case EOM_OUTPUT_TYPE_DISPLAYPORT:			szErrorVal = "EOM_OUTPUT_TYPE_DISPLAYPORT";		break;
	case EOM_OUTPUT_TYPE_HDMIA:					szErrorVal = "EOM_OUTPUT_TYPE_HDMIA";			break;
	case EOM_OUTPUT_TYPE_HDMIB:					szErrorVal = "EOM_OUTPUT_TYPE_HDMIB";			break;
	case EOM_OUTPUT_TYPE_TV:					szErrorVal = "EOM_OUTPUT_TYPE_TV";				break;
	case EOM_OUTPUT_TYPE_EDP:					szErrorVal = "EOM_OUTPUT_TYPE_EDP";				break;
	case EOM_OUTPUT_TYPE_VIRTUAL:				szErrorVal = "EOM_OUTPUT_TYPE_VIRTUAL";			break;
	case EOM_OUTPUT_TYPE_DSI:					szErrorVal = "EOM_OUTPUT_TYPE_DSI";				break;
	case EOM_OUTPUT_TYPE_MAX:					szErrorVal = "EOM_OUTPUT_TYPE_MAX";				break;
	default:									szErrorVal = "Unknown Type";					break;
	}

	return szErrorVal;
}

/**
* @function 		EomGetExternalOutputMode
* @description	 	Maps mode enums to string values
* @parameter		nMode : mode value returned
* @return 			mode value string
*/
char* EomGetExternalOutputMode(int nMode)
{
	char *szErrorVal = NULL;
	switch ( nMode )
	{
	case EOM_OUTPUT_MODE_NONE:				szErrorVal = " EOM_OUTPUT_MODE_NONE";			break;
	case EOM_OUTPUT_MODE_MIRROR:			szErrorVal = "EOM_OUTPUT_MODE_MIRROR";			break;
	case EOM_OUTPUT_MODE_PRESENTATION:		szErrorVal = "EOM_OUTPUT_MODE_PRESENTATION";	break;
	case EOM_OUTPUT_MODE_MAX:				szErrorVal = " EOM_OUTPUT_MODE_MAX";			break;
	default:								szErrorVal = "Unknown Mode";					break;
	}

	return szErrorVal;
}

/**
* @function 		EomGetAttribute
* @description	 	Maps attribute enums to string values
* @parameter		nAtribute : attribute code returned
* @return 			attribute string
*/
char* EomGetAttribute(int nAtribute)
{
	char *szErrorVal = NULL;

	switch ( nAtribute )
	{
	case EOM_OUTPUT_ATTRIBUTE_NONE:					szErrorVal = "EOM_OUTPUT_ATTRIBUTE_NONE";					break;
	case EOM_OUTPUT_ATTRIBUTE_NORMAL:				szErrorVal = "EOM_OUTPUT_ATTRIBUTE_NORMAL";					break;
	case EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE_SHARE:		szErrorVal = "EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE_SHARE";		break;
	case EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE:			szErrorVal = "EOM_OUTPUT_ATTRIBUTE_EXCLUSIVE";				break;
	case EOM_OUTPUT_ATTRIBUTE_MAX:					szErrorVal = "EOM_OUTPUT_ATTRIBUTE_MAX";					break;
	default:										szErrorVal = "Unknown Attribute";							break;
	}

	return szErrorVal;
}

/**
* @function 		EomGetAtributeState
* @description	 	Maps state enums to string values
* @parameter		nState : state code returned
* @return 			state value string
*/
char* EomGetAtributeState(int nState)
{
	char *szErrorVal = NULL;
	switch ( nState )
	{
	case EOM_OUTPUT_ATTRIBUTE_STATE_NONE:			szErrorVal = "EOM_OUTPUT_ATTRIBUTE_STATE_NONE";			break;
	case EOM_OUTPUT_ATTRIBUTE_STATE_ACTIVE:			szErrorVal = "EOM_OUTPUT_ATTRIBUTE_STATE_ACTIVE";		break;
	case EOM_OUTPUT_ATTRIBUTE_STATE_INACTIVE:		szErrorVal = "EOM_OUTPUT_ATTRIBUTE_STATE_INACTIVE";		break;
	case EOM_OUTPUT_ATTRIBUTE_STATE_LOST:			szErrorVal = "EOM_OUTPUT_ATTRIBUTE_STATE_LOST";			break;
	case EOM_OUTPUT_ATTRIBUTE_STATE_MAX:			szErrorVal = "EOM_OUTPUT_ATTRIBUTE_STATE_MAX";			break;
	default:										szErrorVal = "Unknown State";							break;
	}

	return szErrorVal;
}

/**
* @function 		EomTimeout
* @description	 	Called if some callback is not invoked for a particular EomTimeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean EomTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
		g_main_loop_unref(pMainLoop);
		pMainLoop = NULL;
	}
	FPRINTF("[Line : %d][%s] Callback DeviceTimeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/** @} */
