//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-cion-common.h"

/** @addtogroup itc-cion
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 					CionGetError
* @description 					print the error information
* @parameter[in]				nResult: the error code
* @return 						pszErrorMsg: return the error message
*/
char *CionGetError(int nResult)
{
	char *pszErrorMsg = "UNDEFINED ERROR \n";

	switch ( nResult )
	{
	case CION_ERROR_NONE :
		pszErrorMsg = "CION_ERROR_NONE  \n";
		break;
	case CION_ERROR_IO_ERROR :
		pszErrorMsg = "CION_ERROR_IO_ERROR \n";
		break;
	case CION_ERROR_OUT_OF_MEMORY :
		pszErrorMsg = "CION_ERROR_OUT_OF_MEMORY \n";
		break;
	case CION_ERROR_PERMISSION_DENIED :
		pszErrorMsg = "CION_ERROR_PERMISSION_DENIED \n";
		break;
	case CION_ERROR_INVALID_PARAMETER :
		pszErrorMsg = "CION_ERROR_INVALID_PARAMETER  \n";
		break;
	case CION_ERROR_INVALID_OPERATION:
		pszErrorMsg = "CION_ERROR_INVALID_OPERATION \n";
		break;
	case CION_ERROR_ALREADY_IN_PROGRESS:
		pszErrorMsg = "CION_ERROR_ALREADY_IN_PROGRESS \n";
		break;
	case CION_ERROR_NOT_SUPPORTED :
		pszErrorMsg = "CION_ERROR_NOT_SUPPORTED  \n";
		break;
	case CION_ERROR_TIMED_OUT :
		pszErrorMsg = "CION_ERROR_TIMED_OUT \n";
		break;
	case CION_ERROR_OPERATION_FAILED :
		pszErrorMsg = "CION_ERROR_OPERATION_FAILED  \n";
		break;
	default:
		break;
	}
	return pszErrorMsg;
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

/** @} */
