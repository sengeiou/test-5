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
#include "ITs-nsd-common.h"

/** @addtogroup itc-nsd
*  @ingroup itc
*  @{
*/

/**
* @function 		NsdSsdpGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* NsdSsdpGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case SSDP_ERROR_NONE:						szErrorVal = "SSDP_ERROR_NONE";							break;
	case SSDP_ERROR_OUT_OF_MEMORY:				szErrorVal = "SSDP_ERROR_OUT_OF_MEMORY";				break;
	case SSDP_ERROR_INVALID_PARAMETER:			szErrorVal = "SSDP_ERROR_INVALID_PARAMETER";			break;
	case SSDP_ERROR_NOT_SUPPORTED:				szErrorVal = "SSDP_ERROR_NOT_SUPPORTED";				break;
	case SSDP_ERROR_NOT_INITIALIZED:			szErrorVal = "SSDP_ERROR_NOT_INITIALIZED";				break;
	case SSDP_ERROR_OPERATION_FAILED:			szErrorVal = "SSDP_ERROR_OPERATION_FAILED";				break;
	case SSDP_ERROR_SERVICE_NOT_FOUND:			szErrorVal = "SSDP_ERROR_SERVICE_NOT_FOUND";			break;
	case SSDP_ERROR_SERVICE_ALREADY_REGISTERED:	szErrorVal = "SSDP_ERROR_SERVICE_ALREADY_REGISTERED";	break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		NsdDnsSdGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* NsdDnsSdGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case DNSSD_ERROR_NONE:						szErrorVal = "DNSSD_ERROR_NONE";						break;
	case DNSSD_ERROR_OUT_OF_MEMORY:				szErrorVal = "DNSSD_ERROR_OUT_OF_MEMORY";				break;
	case DNSSD_ERROR_INVALID_OPERATION:			szErrorVal = "DNSSD_ERROR_INVALID_OPERATION";			break;
	case DNSSD_ERROR_INVALID_PARAMETER:			szErrorVal = "DNSSD_ERROR_INVALID_PARAMETER";			break;
	case DNSSD_ERROR_NOT_SUPPORTED:				szErrorVal = "DNSSD_ERROR_NOT_SUPPORTED";				break;
	case DNSSD_ERROR_NOT_INITIALIZED:			szErrorVal = "DNSSD_ERROR_NOT_INITIALIZED";				break;
	case DNSSD_ERROR_ALREADY_REGISTERED:		szErrorVal = "DNSSD_ERROR_ALREADY_REGISTERED";			break;
	case DNSSD_ERROR_NAME_CONFLICT:				szErrorVal = "DNSSD_ERROR_NAME_CONFLICT";				break;
	case DNSSD_ERROR_SERVICE_NOT_RUNNING:		szErrorVal = "DNSSD_ERROR_SERVICE_NOT_RUNNING";			break;
	case DNSSD_ERROR_SERVICE_NOT_FOUND:			szErrorVal = "DNSSD_ERROR_SERVICE_NOT_FOUND";			break;
	case DNSSD_ERROR_OPERATION_FAILED:			szErrorVal = "DNSSD_ERROR_OPERATION_FAILED";			break;
	default:									szErrorVal = "Unknown Error";							break;
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
	return false;
}

/** @} */