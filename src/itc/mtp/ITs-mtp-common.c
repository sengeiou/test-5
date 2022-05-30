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
#include "ITs-mtp-common.h"

/** @addtogroup itc-mtp
*  @ingroup itc
*  @{
*/

/**
* @function 					MTPGetError
* @description 					print the error information
* @parameter[in]				nResult: the error code
* @return 						pszErrorMsg: return the error message
*/
char *MTPGetError(int nResult)
{
	char *pszErrorMsg = NULL;

	switch ( nResult )
	{
	case MTP_ERROR_NONE :
		pszErrorMsg = "MTP_ERROR_NONE  \n";
		break;
	case MTP_ERROR_IO_ERROR :
		pszErrorMsg = "MTP_ERROR_IO_ERROR  \n";
		break;
	case MTP_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "MTP_ERROR_INVALID_PARAMETER  \n";
		break;
	case MTP_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "MTP_ERROR_OUT_OF_MEMORY  \n";
		break;
	case MTP_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "MTP_ERROR_PERMISSION_DENIED  \n";
		break;
	case MTP_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "MTP_ERROR_NOT_SUPPORTED  \n";
		break;
	case MTP_ERROR_COMM_ERROR :
		pszErrorMsg = "MTP_ERROR_COMM_ERROR  \n";
		break;
	case MTP_ERROR_CONTROLLER :
		pszErrorMsg = "MTP_ERROR_CONTROLLER  \n";
		break;
	case MTP_ERROR_NO_DEVICE :
		pszErrorMsg = "MTP_ERROR_NO_DEVICE  \n";
		break;
	case MTP_ERROR_NOT_INITIALIZED :
		pszErrorMsg = "MTP_ERROR_NOT_INITIALIZED  \n";
		break;
	case MTP_ERROR_NOT_ACTIVATED :
		pszErrorMsg = "MTP_ERROR_NOT_ACTIVATED  \n";
		break;
	case MTP_ERROR_NOT_COMM_INITIALIZED :
		pszErrorMsg = "MTP_ERROR_NOT_COMM_INITIALIZED  \n";
		break;
	case MTP_ERROR_PLUGIN_FAIL :
		pszErrorMsg = "MTP_ERROR_PLUGIN_FAIL  \n";
		break;
	default:
		pszErrorMsg = "UNDEFINED ERROR \n";
		break;
	}
	return pszErrorMsg;
}

/** @} */