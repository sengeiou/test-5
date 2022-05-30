//
// Copyright (c) 2019 Samsung Electronics Co., Ltd.
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
#include "ITs-autofill-common.h"

/** @addtogroup itc-autofill
*  @ingroup itc
*  @{
*/

/**
* @function 		AutofillGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AutofillGetError(autofill_error_e nRet)
{
	char *pszErrorVal = NULL;
	switch ( nRet )
	{
	case AUTOFILL_ERROR_NONE : 							pszErrorVal = "AUTOFILL_ERROR_NONE"; 							break;/**< Successful */
	case AUTOFILL_ERROR_INVALID_PARAMETER : 				pszErrorVal = "AUTOFILL_ERROR_INVALID_PARAMETER"; 				break;/**< Invalid parameter */
	case AUTOFILL_ERROR_OUT_OF_MEMORY: 					pszErrorVal = "AUTOFILL_ERROR_OUT_OF_MEMORY"; 					break;/**< Out of memory error */
	case AUTOFILL_ERROR_OPERATION_FAILED : 				pszErrorVal = "AUTOFILL_ERROR_OPERATION_FAILED"; 				break;/**< Operation failed */
	case AUTOFILL_ERROR_PERMISSION_DENIED : 				pszErrorVal = "AUTOFILL_ERROR_PERMISSION_DENIED"; 				break;/**< Permission denied */
	case AUTOFILL_ERROR_NOT_INITIALIZED : 				pszErrorVal = "AUTOFILL_ERROR_NOT_INITIALIZED"; 				break;/**< Not initialized */
	default : 												pszErrorVal = "Unknown Error"; 									break;
	}
	return pszErrorVal;
}

/**
* @function 		ApplicationGetDataPath
* @description	 	Returnes the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool ApplicationGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line : %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line : %d][%s] Unable to get application data path; app_get_data_path returned null value \\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, strlen(pPath)+1);
	FREE_MEMORY(pPath);

	FPRINTF("[Line : %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}


/** @} */
