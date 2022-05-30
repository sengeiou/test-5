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
#include "ITs-metadata-editor-common.h"

/** @addtogroup itc-metadata-editor
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
* @function 		MetadataEditorAppendToAppDataPath
* @description	 	Appends the input string to application data path
* @parameter		pInputPath: path to append to data path; pFinalPath: final resultant path
* @return 			true if succeed else false
*/
bool MetadataEditorAppendToAppDataPath(char* pInputPath, char* pFinalPath)
{
	if ( NULL == pInputPath || NULL == pFinalPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	char pAppDataPath[PATH_LEN] = {0,};
	if ( false == MetadataEditorGetDataPath(pAppDataPath) )
	{
		return false;
	}

	memset(pFinalPath, 0, PATH_LEN);
	strncpy(pFinalPath, pAppDataPath, PATH_LEN-1);
	strncat(pFinalPath, pInputPath, strlen(pInputPath)+1);

	FPRINTF("[Line: %d][%s] result path returned = %s\\n", __LINE__, API_NAMESPACE, pFinalPath);
	return true;
}

/**
* @function 		MetadataEditorGetDataPath
* @description	 	Returns the application data path
* @parameter		pAppDataPath: application data path
* @return 			true if succeed else false
*/
bool MetadataEditorGetDataPath(char* pAppDataPath)
{
	if ( NULL == pAppDataPath )
	{
		FPRINTF("[Line: %d][%s] Null Path provided; Check the input string\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	memset(pAppDataPath, 0, PATH_LEN);

	char* pPath = NULL;
	pPath = app_get_data_path();
	if ( NULL == pPath )
	{
		FPRINTF("[Line: %d][%s] Unable to get application data path; app_get_data_path returned null value\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	strncpy(pAppDataPath, pPath, PATH_LEN-1);

	FPRINTF("[Line: %d][%s] application data path returned = %s\\n", __LINE__, API_NAMESPACE, pAppDataPath);

	return true;
}

/**
* @function 		Metadata_EditorGetError
* @description	 	Maps error enums to string values
* @parameter		nRet: error code returned
* @return 			error string
*/
char* Metadata_EditorGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case METADATA_EDITOR_ERROR_NONE: 				szErrorVal = "TIZEN_ERROR_NONE";			 					break;
	case METADATA_EDITOR_ERROR_INVALID_PARAMETER: 	szErrorVal = "METADATA_EDITOR_ERROR_INVALID_PARAMETER"; 		break;
	case METADATA_EDITOR_ERROR_OUT_OF_MEMORY: 		szErrorVal = "METADATA_EDITOR_ERROR_OUT_OF_MEMORY";		 		break;
	case METADATA_EDITOR_ERROR_OPERATION_FAILED: 	szErrorVal = "METADATA_EDITOR_ERROR_OPERATION_FAILED"; 			break;
	case METADATA_EDITOR_ERROR_FILE_EXISTS: 		szErrorVal = "METADATA_EDITOR_ERROR_FILE_EXISTS"; 				break;
	case METADATA_EDITOR_ERROR_PERMISSION_DENIED: 	szErrorVal = "TIZEN_ERROR_PERMISSION_DENIED"; 					break;
	case METADATA_EDITOR_ERROR_NOT_SUPPORTED: 		szErrorVal = "TIZEN_ERROR_NOT_SUPPORTED"; 						break;
	case METADATA_EDITOR_ERROR_METADATA_UPDATE_NOT_POSSIBLE:	szErrorVal = "TIZEN_ERROR_METADATA_UPDATE_NOT_POSSIBLE";	break;
	default:										szErrorVal = "Unknown Error";									break;
	}
	return szErrorVal;
}

/** @} */ //end of itc-metadata-editor
