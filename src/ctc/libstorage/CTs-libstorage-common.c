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
#include "CTs-libstorage-common.h"

/** @addtogroup ctc-libstorage
* @ingroup		ctc
* @{
*/

//Add helper function definitions here
/**
* @function 			FileClose
* @description 			File closing form open state
* @parameter	[IN]	pFilePath [tha file path to be closed].
* @pre-condition		NA
* @return 				true if File closed successfully otherwise false.
*/
bool FileClose(FILE *pFile)
{
	int nRet = -1;
	nRet = fclose(pFile);
	if ( nRet != 0 )
	{
		FPRINTF("[Line : %d][%s] File Closing failed.\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	return true;
}

/**
* @function 			FileRemove
* @description 			File removing by file path
* @parameter	[IN]	pFilePath [tha file path to be removed].
* @pre-condition		NA
* @return 				true if File Removed successfully otherwise false.
*/
bool FileRemove(char* pFilePath)
{
	int nRet = -1;
	nRet = remove(pFilePath);
	if ( nRet < 0 )
	{
		FPRINTF("[Line : %d][%s] File removing failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	return true;
}
/**
* @function 			FileCopy
* @description 			Copy one file with contents to another file.
* @parameter	[IN]	pSrcFile [Source file].
*				[IN]    pszSrcFilePath [Source file path].
*				[IN]    pDestFile [Destination file].
*				[IN]    pszDestFilePath [Destination file path].
* @pre-condition		NA
* @return 				true if File copied successfully otherwise false.
*/
bool FileCopy(char *pszSrcFilePath, char  *pszDestFilePath)
{
	char szBuffer[MAXVAL] = {0};    /*Buffer to store files content*/
	FILE  *pSrcFile = NULL;
	FILE  *pDestFile = NULL;
	pSrcFile = fopen(pszSrcFilePath, "r");
	if ( pSrcFile == NULL )
	{
		FPRINTF("[Line : %d][%s] Source File Opening failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	pDestFile = fopen(pszDestFilePath, "w");
	if ( pDestFile == NULL )
	{
		FPRINTF("[Line : %d][%s] Destination File Opening failed\\n", __LINE__, API_NAMESPACE);
		FileClose(pSrcFile);
		return  false;
	}

	while ( fgets(szBuffer, MAXVAL, pSrcFile) )
	{
		fputs(szBuffer, pDestFile);
	}

	FPRINTF("[Line : %d][%s] File Copied successfully\\n", __LINE__, API_NAMESPACE);
	FileClose(pSrcFile);
	FileClose(pDestFile);
	return  true;
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
	case STORAGE_ERROR_NONE:					pszErrorMsg = "STORAGE_ERROR_NONE";					break;
	case STORAGE_ERROR_INVALID_PARAMETER:		pszErrorMsg = "STORAGE_ERROR_INVALID_PARAMETER";	break;
	case STORAGE_ERROR_OUT_OF_MEMORY:			pszErrorMsg = "STORAGE_ERROR_OUT_OF_MEMORY";		break;
	case STORAGE_ERROR_NOT_SUPPORTED:			pszErrorMsg = "STORAGE_ERROR_NOT_SUPPORTED";		break;
	case STORAGE_ERROR_OPERATION_FAILED:		pszErrorMsg = "STORAGE_ERROR_OPERATION_FAILED";		break;
	default:									pszErrorMsg = "Unknown Error";
	}
	
	return pszErrorMsg;
}

/**
* @function 			AppendFileName
* @description			Append file name 
* @parameter	[IN]	pszDirPath -dir path
* @parameter	[OUT]	pszTragetPath -absolute file path
* @return 				NULL
*/
void AppendFileName(char *pszDirPath, char *pszTragetPath)
{
	strncpy(pszTragetPath, pszDirPath, strlen(pszDirPath)+1);
	strncat(pszTragetPath, "/newFile.txt", strlen("/newFile.txt")+1);
	FPRINTF("[Line : %d][%s] File path : %s\\n", __LINE__, API_NAMESPACE, pszTragetPath);
}

/**
* @function 			FileOpen
* @description			Open file
* @parameter	[IN]	pszDirPath -dir path
* @parameter	[OUT]	pszTragetPath -absolute file path
* @return 				return FILE *pFile
*/
FILE *FileOpen(char *pszDirPath, char *pszTragetPath)
{
	AppendFileName(pszDirPath, pszTragetPath);
	FILE *pFile = fopen(pszTragetPath, "w+");
	return pFile;
}


/**
* @function 			IsPathValid
* @description			check path validity
* @parameter	[IN]	pszPath -path
* @return 				If true on valid path otherwise false
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

/** @} */ //end of ctc-libstorage
