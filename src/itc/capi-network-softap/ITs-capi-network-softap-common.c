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

#include "ITs-capi-network-softap-common.h"



/**
* @function             SoftApGetError
* @description          Maps error enums to string values
* @parameter            nRet : error code returned
* @return                       error string
*/
char* SoftApGetError(int nRet)
{
        char *szErrorVal = NULL;

        switch ( nRet )
        {
        case SOFTAP_ERROR_NONE:                             szErrorVal = "SOFTAP_ERROR_NONE";                              break;
        case SOFTAP_ERROR_INVALID_PARAMETER:   		    szErrorVal = "SOFTAP_ERROR_INVALID_PARAMETER";    break;
        case SOFTAP_ERROR_OUT_OF_MEMORY:                    szErrorVal = "SOFTAP_ERROR_OUT_OF_MEMORY";                  break;
	case SOFTAP_ERROR_RESOURCE_BUSY:		    szErrorVal = "SOFTAP_ERROR_RESOURCE_BUSY";    break;
	case SOFTAP_ERROR_OPERATION_FAILED:		    szErrorVal = "SOFTAP_ERROR_OPERATION_FAILED";   break;
	case SOFTAP_ERROR_ALREADY_ENABLED:		    szErrorVal = "SOFTAP_ERROR_ALREADY_ENABLED";    break;
	case SOFTAP_ERROR_INVALID_OPERATION:		    szErrorVal = "SOFTAP_ERROR_INVALID_OPERATION";  break;
	case SOFTAP_ERROR_NOT_SUPPORTED:                    szErrorVal = "SOFTAP_ERROR_NOT_SUPPORTED";   break;
	case SOFTAP_ERROR_PERMISSION_DENIED:		    szErrorVal = "SOFTAP_ERROR_PERMISSION_DENIED";  break;
        default:                                            szErrorVal = "Unknown Error";  break;
        }
        return szErrorVal;
}
