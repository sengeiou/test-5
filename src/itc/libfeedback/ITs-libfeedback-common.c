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
#include "ITs-libfeedback-common.h"
//Add helper function definitions here


/**
 * @function 		FeedbackGetError
 * @description	 	Maps error enums to string values
 * @parameter		nRet : error code returned
 * @return 			error string
 */
char *FeedbackGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch(nRet)
	{
		case FEEDBACK_ERROR_NONE : szErrorVal = "FEEDBACK_ERROR_NONE " ; break; 
		case FEEDBACK_ERROR_INVALID_PARAMETER : szErrorVal = "FEEDBACK_ERROR_INVALID_PARAMETER" ; break; 
		case FEEDBACK_ERROR_NOT_INITIALIZED : szErrorVal = "FEEDBACK_ERROR_NOT_INITIALIZED" ; break; 
		case FEEDBACK_ERROR_OPERATION_FAILED : szErrorVal = "FEEDBACK_ERROR_OPERATION_FAILED" ; break;
		case FEEDBACK_ERROR_PERMISSION_DENIED : szErrorVal = "FEEDBACK_ERROR_PERMISSION_DENIED" ; break; 
		case FEEDBACK_ERROR_NOT_SUPPORTED : szErrorVal = "FEEDBACK_ERROR_NOT_SUPPORTED" ; break;
		default : szErrorVal = "Unknown Error" ; break;
	}

	return szErrorVal;
}
