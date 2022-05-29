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
#include "CTs-runtime-info-common.h"

/** @addtogroup ctc-runtime-info
* @ingroup		ctc
* @{
*/

//Add helper function definitions here

/**
* @function 					RuntimeGetSystemState
* @description 					Gets the boolean value from the runtime information
* @parameter[IN]				eRuntimeInfoKey, Enumeration for keys for runtime information
* @return 						True if runtime_info_get_value_bool passed otherwise false
*/
bool RuntimeGetSystemState(runtime_info_key_e eRuntimeInfoKey)
{
	g_bRuntimeKeyState = false;
	g_bRuntimeKeyNotSupported = false;
	int nRet = runtime_info_get_value_bool(eRuntimeInfoKey, &g_bRuntimeKeyState);
	if ( nRet != RUNTIME_INFO_ERROR_NONE )
	{
		if (nRet == TIZEN_ERROR_NOT_SUPPORTED)
		{
			g_bRuntimeKeyNotSupported = true;
			return true;	
		}

		FPRINTF("[Line : %d][%s] runtime_info_get_value_bool is failed, error returned = %s\\n", __LINE__, API_NAMESPACE, RuntimeGetError(nRet));
		return false;
	}

	return true;
}

/**
* @function 					RuntimeGetError
* @description 					print the error of runtime information
* @parameter[IN]				nResult, the error code
* @return 						NA
*/
char* RuntimeGetError(int nResult)
{
	char* pszErrInfo = NULL;
	
	switch ( nResult )
	{
	case RUNTIME_INFO_ERROR_INVALID_PARAMETER:		pszErrInfo = "RUNTIME_INFO_ERROR_INVALID_PARAMETER";	break;
	case RUNTIME_INFO_ERROR_OUT_OF_MEMORY:			pszErrInfo = "RUNTIME_INFO_ERROR_OUT_OF_MEMORY";		break;
	case RUNTIME_INFO_ERROR_IO_ERROR:				pszErrInfo = "RUNTIME_INFO_ERROR_IO_ERROR";				break;
	case RUNTIME_INFO_ERROR_PERMISSION_DENIED:		pszErrInfo = "RUNTIME_INFO_ERROR_PERMISSION_DENIED";	break; 
	default:										pszErrInfo = "UNKNOWN";
	}
	
	return pszErrInfo;
}

/** @} */ //end of ctc-runtime-info
