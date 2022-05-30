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
#include "CTs-filesystem-permission-common.h"

/** @addtogroup ctc-filesystem-permission
* @ingroup		ctc
* @{
*/

/**
* @function 			FilePermissionCreateFile
* @description			Create a file to the specified location
* @parameter	[IN]	nStorageID -Storage ID
* 				[IN]	eStorageDirectory -Enumeration of the storage directory types
* @return 				If get root directory and create file successfully or not supported occure it returns true otherwise false
*/
bool FilePermissionCreateFile(int nStorageID, storage_directory_e eStorageDirectory) 
{
	int nRet = STORAGE_ERROR_NONE;
	FILE *pFile = NULL;	
	char* pszFilePath;
	char* pszPath;

	nRet = storage_get_directory(nStorageID, eStorageDirectory, &pszFilePath);
	if ( nRet != STORAGE_ERROR_NONE && nRet != STORAGE_ERROR_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] storage_get_directory failed, error returned = %s (%d)\n\\n", __LINE__, API_NAMESPACE, StorageGetError(nRet), nRet);
		return false;
	}
	if ( nRet == STORAGE_ERROR_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] Storage Not Supported\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		return true;
	}

	if ( pszFilePath == NULL || strlen(pszFilePath) == 0 )
	{
		FPRINTF("[Line : %d][%s] No path is found under directory\\n", __LINE__, API_NAMESPACE);
		return  false;
	}
	if ( IsPathValid(pszFilePath) == false )
	{
		FPRINTF("[Line : %d][%s] Directory does not exist\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		return  true;
	}
	FPRINTF("[Line : %d][%s] Storage Directory : %s\\n", __LINE__, API_NAMESPACE, pszFilePath);
	pszPath = (char*)malloc(1 + strlen(pszFilePath) + strlen( "/newFile.txt"));

	if(pszPath == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		return  false;
	}
	
	strncpy(pszPath, pszFilePath, strlen(pszFilePath)+1);
	strncat(pszPath, "/newFile.txt", strlen("/newFile.txt")+1);

	pFile = fopen(pszPath, "w+");
	if ( pFile == NULL )
	{
		FPRINTF("[Line : %d][%s] File is not created in %s with error %s and error no is %d\\n", __LINE__, API_NAMESPACE, pszFilePath, strerror( errno ), errno);
		FREE_MEMORY(pszPath);
		FREE_MEMORY(pszFilePath);
		return false;
	}

	nRet = fclose(pFile);
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] File close is failed in %s with error %s and error no is %d\\n", __LINE__, API_NAMESPACE, pszFilePath, strerror( errno ), errno);
	}

	nRet = remove(pszPath);
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] File remove is failed in %s with error %s and error no is %d\\n", __LINE__, API_NAMESPACE, pszFilePath, strerror( errno ), errno);
	}
	pFile = NULL;

	FPRINTF("[Line : %d][%s] File is created in %s\\n", __LINE__, API_NAMESPACE, pszPath);

	FREE_MEMORY(pszPath);
	FREE_MEMORY(pszFilePath);
	return true;
}

/**
* @function 	IsPathValid
* @description  check path validity
* @parameter	[IN] pszPath -path
* @return 		If true on valid path otherwise false
* 
*/
bool IsPathValid(char *pszPath) 
{
	struct stat st;
	if ( stat(pszPath,&st) == 0 )
	{
		return true; // directory present
	}
	return false;
}

/**
* @function 			FilePermissionCreateDirectory
* @description			Get root directory and Create a file to the specified location
* @parameter	[IN]	nStorageID -Storage ID (internal or external)
* 				[IN]	eStorageDirectory -Enumeration of the storage directory types
* @return 				If get root directory and create directory successfully or not supported occurs it returns true otherwise false
*/
bool FilePermissionCreateDirectory(int nStorageID, storage_directory_e eStorageDirectory) 
{
	int nRet = STORAGE_ERROR_NONE;

	char* pszFilePath;
	char* pszPath;

	nRet = storage_get_directory(nStorageID, eStorageDirectory, &pszFilePath);
	if ( nRet != STORAGE_ERROR_NONE && nRet != STORAGE_ERROR_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] storage_get_directory failed, error returned = %s (%d)\n\\n", __LINE__, API_NAMESPACE, StorageGetError(nRet), nRet);
		return false;
	}
	if ( nRet == STORAGE_ERROR_NOT_SUPPORTED )
	{
		FPRINTF("[Line : %d][%s] Storage Not Supported\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		return true;
	}

	if ( pszFilePath == NULL || strlen(pszFilePath) == 0 )
	{
		FPRINTF("[Line : %d][%s] No path is found under directory\\n", __LINE__, API_NAMESPACE);
		return  false;
	}

	FPRINTF("[Line : %d][%s] Storage Directory : %s\\n", __LINE__, API_NAMESPACE, pszFilePath);

	pszPath = (char*)malloc(1 + strlen(pszFilePath) + strlen( "/testFolder"));

	if(pszPath == NULL)
	{
		FPRINTF("[Line : %d][%s] Unable to allocate memory\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		return  false;
	}
	
	strncpy(pszPath, pszFilePath, strlen(pszFilePath)+1);

	if ( IsPathValid(pszFilePath) == false )
	{
		FPRINTF("[Line : %d][%s] Directory does not exist\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszFilePath);
		FREE_MEMORY(pszPath);
		return  true;
	}	
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] Directory is not created in %s\\n", __LINE__, API_NAMESPACE, pszPath);
		FREE_MEMORY(pszPath);
		FREE_MEMORY(pszFilePath);
		return false;
	}

	strncat(pszPath, "/testFolder", strlen("/testFolder")+1);

	nRet = mkdir(pszPath, 0777);
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] Directory creation is failed in %s\\n", __LINE__, API_NAMESPACE, pszPath);
	}

	nRet = rmdir(pszPath);
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] Directory remove is failed in %s\\n", __LINE__, API_NAMESPACE, pszPath);
	}

	FPRINTF("[Line : %d][%s] Directory is created in %s\\n", __LINE__, API_NAMESPACE, pszPath);

	FREE_MEMORY(pszPath);
	FREE_MEMORY(pszFilePath);
	return true;
}

/**
* @function 			StorageGetError
* @description 			print the error information
* @parameter	[IN]	nResult, the error code
* 				[IN]	pszApiName, API name
* @return 				NA
*/
char* StorageGetError(int nResult)
{
	char *pszErrorMsg = NULL;
	
	switch ( nResult )
	{
	case STORAGE_ERROR_NONE:					pszErrorMsg = "STORAGE_ERROR_NONE";						break;
	case STORAGE_ERROR_INVALID_PARAMETER:		pszErrorMsg = "STORAGE_ERROR_INVALID_PARAMETER";		break;
	case STORAGE_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "STORAGE_ERROR_OUT_OF_MEMORY";			break;
	case STORAGE_ERROR_NOT_SUPPORTED:			pszErrorMsg = "STORAGE_ERROR_NOT_SUPPORTED";			break;
	case STORAGE_ERROR_OPERATION_FAILED:		pszErrorMsg = "STORAGE_ERROR_OPERATION_FAILED";			break;
	default:									pszErrorMsg = "Unknown Error";
	}
	
	return pszErrorMsg;
}

/** @} */ //end of ctc-filesystem-permission
