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
#include "ITs-vpn-service-common.h"

/** @addtogroup itc-vpn-service
*  @ingroup itc
*  @{
*/

/**
* @function 					VPNSVCGetError
* @description 					print the error information
* @parameter[in]				nResult: the error code
* @return 						pszErrorMsg: return the error message
*/
char *VPNSVCGetError(int nResult)
{
	char *pszErrorMsg = NULL;

	switch ( nResult )
	{
	case VPNSVC_ERROR_NONE :
		pszErrorMsg = "VPNSVC_ERROR_NONE  \n";
		break;
	case VPNSVC_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "VPNSVC_ERROR_INVALID_PARAMETER  \n";
		break;
	case VPNSVC_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "VPNSVC_ERROR_OUT_OF_MEMORY  \n";
		break;
	case VPNSVC_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "VPNSVC_ERROR_PERMISSION_DENIED  \n";
		break;
	case VPNSVC_ERROR_NO_SUCH_FILE :
		pszErrorMsg = "VPNSVC_ERROR_NO_SUCH_FILE  \n";
		break;
	case VPNSVC_ERROR_IO_ERROR :
		pszErrorMsg = "VPNSVC_ERROR_IO_ERROR  \n";
		break;
	case VPNSVC_ERROR_TIMEOUT :
		pszErrorMsg = "VPNSVC_ERROR_TIMEOUT  \n";
		break;
	case VPNSVC_ERROR_IPC_FAILED :
		pszErrorMsg = "VPNSVC_ERROR_IPC_FAILED  \n";
		break;
	case VPNSVC_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "VPNSVC_ERROR_NOT_SUPPORTED  \n";
		break;
	default:
		pszErrorMsg = "UNDEFINED ERROR \n";
		break;
	}
	return pszErrorMsg;
}

/** @} */