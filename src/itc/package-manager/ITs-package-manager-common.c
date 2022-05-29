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
#include "ITs-package-manager-common.h"

/** @addtogroup itc-package-manager
*  @ingroup itc
*  @{
*/
//Add helper function definitions here

/**
* @function 		PackageManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* PackageManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PACKAGE_MANAGER_ERROR_INVALID_PARAMETER:	szErrorVal = "PACKAGE_MANAGER_ERROR_INVALID_PARAMETER";		break;
	case PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY:		szErrorVal = "PACKAGE_MANAGER_ERROR_OUT_OF_MEMORY";			break;
	case PACKAGE_MANAGER_ERROR_IO_ERROR:			szErrorVal = "PACKAGE_MANAGER_ERROR_IO_ERROR";				break;
	case PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE:		szErrorVal = "PACKAGE_MANAGER_ERROR_NO_SUCH_PACKAGE";		break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function 		PackageManagerGetEnum
* @description	 	Maps enum to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* PackageManagerGetEnum(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PACKAGE_MANAGER_REQUEST_MODE_QUIET:		szErrorVal = "PACKAGE_MANAGER_REQUEST_MODE_QUIET";		break;
	case PACKAGE_MANAGER_REQUEST_MODE_DEFAULT:		szErrorVal = "PACKAGE_MANAGER_REQUEST_MODE_DEFAULT";	break;
	default:										szErrorVal = "Unknown Request";							break;
	}
	return szErrorVal;
}

/**
* @function 		PackageManagerGetEnumForComponent
* @description	 	Maps enum to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* PackageManagerGetEnumForComponent(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case PACKAGE_INFO_APP_COMPONENT_TYPE_ALL:			szErrorVal = "PACKAGE_INFO_APP_COMPONENT_TYPE_ALL";			break;
	case PACKAGE_INFO_APP_COMPONENT_TYPE_UI:			szErrorVal = "PACKAGE_INFO_APP_COMPONENT_TYPE_UI";			break;
	case  PACKAGE_INFO_APP_COMPONENT_TYPE_SERVICE:		szErrorVal = " PACKAGE_INFO_APP_COMPONENT_TYPE_SERVICE";		break;
	default:							szErrorVal = "Unknown Info";				break;
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

/**
* @function 		PackageManagerGetEnumForUpdateInfo
* @description	 	Maps enum to string values
* @parameter		nRet : enum code returned
* @return 			enum string
*/
char* PackageManagerGetEnumForUpdateInfo(int nRet)
{
	char *szErrorVal = "Unknown Info";
	switch ( nRet )
	{
		case PACKAGE_UPDATEINFO_TYPE_NONE:		szErrorVal = "PACKAGE_UPDATEINFO_TYPE_NONE";		break;
		case PACKAGE_UPDATEINFO_TYPE_FORCE:		szErrorVal = "PACKAGE_UPDATEINFO_TYPE_FORCE";		break;
		case PACKAGE_UPDATEINFO_TYPE_OPTIONAL:		szErrorVal = "PACKAGE_UPDATEINFO_TYPE_OPTIONAL";	break;
	}
	return szErrorVal;
}

/** @} */
