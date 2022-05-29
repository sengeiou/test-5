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
#include "ITs-mime-type-common.h"

/** @addtogroup itc-mime-type
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
* @function 		MimeTypeGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* MimeTypeGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case MIME_TYPE_ERROR_NONE:					szErrorVal = "MIME_TYPE_ERROR_NONE";					break;
	case MIME_TYPE_ERROR_INVALID_PARAMETER:		szErrorVal = "MIME_TYPE_ERROR_INVALID_PARAMETER";		break;
	case MIME_TYPE_ERROR_OUT_OF_MEMORY:			szErrorVal = "MIME_TYPE_ERROR_OUT_OF_MEMORY";			break;
	case MIME_TYPE_ERROR_IO_ERROR:				szErrorVal = "MIME_TYPE_ERROR_IO_ERROR";				break;
	default:									szErrorVal = "Unknown Error";							break;
	}
	
	return szErrorVal;
}

/**
* @function 			MimeTypeGetDataPath
* @description 			Get the path to application data directory
* @parameter	[IN]	char* pszFileName [file name]
* @return 				Total Path of file "pszFilename"
*/
char* MimeTypeGetDataPath(char *pszFileName)
{
	char *pszAppData =  app_get_data_path(),*pszImgPath = NULL;
	if ( pszAppData == NULL || strlen(pszAppData) == 0 )
	{
		FPRINTF("[Line : %d][%s] app_get_data_path() returned invalid path\\n", __LINE__, API_NAMESPACE);
		return NULL;
	}

	pszImgPath = (char*) calloc(1, strlen(pszAppData) + strlen(pszFileName)+1);
	if (pszImgPath == NULL)
		return NULL;
	snprintf(pszImgPath,  strlen(pszAppData)+strlen(pszFileName)+1, "%s%s",pszAppData, pszFileName );
	return pszImgPath;
}

/** @} */ //end of itc-mime-type
