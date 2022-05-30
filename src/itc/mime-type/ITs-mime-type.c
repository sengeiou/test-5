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

/**
* @function 		ITs_mime_type_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/ 
void ITs_mime_type_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Mime_Type_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/**
* @function 		ITs_mime_type_cleanup
* @description	 	Called after each test, destroys camera handle
* @parameter		NA
* @return 			NA
*/ 
void ITs_mime_type_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Mime_Type_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	itc-mime-type-testcases
* @brief 		Integration testcases for module mime-type
* @ingroup		itc-mime-type
* @{
*/

//& purpose: Gets file extensions for the given MIME type. 
//& type: auto
/**
* @testcase 			ITc_mime_type_get_file_extension_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets file extensions for the given MIME type. 
* @scenario				Get mime-type\n
*						Get file extension
* @apicovered			mime_type_get_mime_type, mime_type_get_file_extension
* @passcase				if mime_type_get_mime_type and mime_type_get_file_extension are successful
* @failcase				if mime_type_get_mime_type or mime_type_get_file_extension fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mime_type_get_file_extension_p(void)
{
	START_TEST;

	char *pcMime_type = NULL;
	int nRet = mime_type_get_mime_type ("png", &pcMime_type);
	PRINT_RESULT(MIME_TYPE_ERROR_NONE, nRet, "mime_type_get_mime_type", MimeTypeGetError(nRet));
	CHECK_HANDLE(pcMime_type,mime_type_get_mime_type);

	char **pcFile_extension = NULL;
	int nLength=0;

	nRet = mime_type_get_file_extension (pcMime_type, &pcFile_extension, &nLength);//target api
	PRINT_RESULT_CLEANUP(MIME_TYPE_ERROR_NONE, nRet, "mime_type_get_file_extension", MimeTypeGetError(nRet), FREE_MEMORY(pcMime_type));
	CHECK_HANDLE(pcFile_extension,mime_type_get_file_extension);
	CHECK_VALUE_INT(nLength,mime_type_get_file_extension);
	
	FPRINTF("[Line : %d][%s] file_extension : %s\\n" , __LINE__, API_NAMESPACE, *pcFile_extension);
	FPRINTF("[Line : %d][%s] length : %d\\n", __LINE__, API_NAMESPACE, nLength);

	FREE_MEMORY(pcFile_extension);
	FREE_MEMORY(pcMime_type);
	return 0;
}

//& purpose: Gets the MIME type for the given file extension. 
//& type: auto
/**
* @testcase 			ITc_mime_type_get_mime_type_p
* @since_tizen 			2.3
* @author            	SRID(parshant.v)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the MIME type for the given file extension. 
* @scenario				Get mime-type using mime_type_get_mime_type
* @apicovered			mime_type_get_mime_type
* @passcase				if mime_type_get_mime_type successful
* @failcase				if mime_type_get_mime_type fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mime_type_get_mime_type_p(void)
{
	START_TEST;
	
	char *pcMime_type = NULL;
	int nRet = mime_type_get_mime_type ("png", &pcMime_type);//target api
	PRINT_RESULT(MIME_TYPE_ERROR_NONE, nRet, "mime_type_get_mime_type", MimeTypeGetError(nRet));
	CHECK_HANDLE(pcMime_type,mime_type_get_mime_type);

	FPRINTF("[Line : %d][%s] mime_type : %s\\n", __LINE__, API_NAMESPACE, pcMime_type);
	FREE_MEMORY(pcMime_type);
	return 0;
}

//& purpose: Gets the MIME type for the given data.
//& type: auto
/**
* @testcase 			ITc_mime_type_get_mime_type_for_data
* @since_tizen 			4.0
* @author            	SRID(samuel.peter)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Gets the MIME type for the given data.
* @scenario				Get mime-type using mime_type_get_mime_type_for_data
* @apicovered			mime_type_get_mime_type_for_data
* @passcase				if mime_type_get_mime_type_for_data successful
* @failcase				if mime_type_get_mime_type_for_data fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mime_type_get_mime_type_for_data(void)
{
	START_TEST;

	char *pszMimeType = NULL;
	char *pszPath = NULL;
	char *pszOutMimeType = "image/jpeg";
	FILE *pFilePtr = NULL;
	int nSize = 0;
	int nRet = 0;
	int nTestFileSize = 50;
	int nRead = 0;
	char pFileData[nTestFileSize];

	pszPath = MimeTypeGetDataPath(SAMPLE_FILE_PATH);
	if ( NULL == pszPath)
	{
		FPRINTF("[Line : %d][%s] MimeTypeGetDataPath failed, error returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	pFilePtr = fopen(pszPath, "rb");
	if(NULL == pFilePtr)
	{
		FPRINTF("[Line : %d][%s] unable to open data file: %s\\n", __LINE__, API_NAMESPACE, pszPath);
		FREE_MEMORY(pszPath);
		return 1;
	}

	nRead = fread(pFileData, 1, nTestFileSize, pFilePtr);
	if(nRead != nTestFileSize)
	{
		FPRINTF("[Line : %d][%s] unable to read data from file.\\n", __LINE__, API_NAMESPACE);
		fclose(pFilePtr);
		FREE_MEMORY(pszPath);
		return 1;
	}

	nSize = sizeof(pFileData);
	nRet = mime_type_get_mime_type_for_data(pFileData, nSize, &pszMimeType);
	PRINT_RESULT_CLEANUP(MIME_TYPE_ERROR_NONE, nRet, "mime_type_get_mime_type_for_data", MimeTypeGetError(nRet), FREE_MEMORY(pszPath);fclose(pFilePtr););
	CHECK_HANDLE(pszMimeType,"mime_type_get_mime_type_for_data");

	nSize = sizeof(pszOutMimeType);
	if(strncmp(pszMimeType, pszOutMimeType, nSize) != 0)
	{
		FPRINTF("[Line : %d][%s] incorrect mime_type returned.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszMimeType);
		FREE_MEMORY(pszPath);
		fclose(pFilePtr);
		return 1;
	}

	FPRINTF("[Line : %d][%s] mime_type : %s\\n", __LINE__, API_NAMESPACE, pszMimeType);
	FREE_MEMORY(pszMimeType);
	FREE_MEMORY(pszPath);
	fclose(pFilePtr);

	return 0;
}

//& purpose: Gets the MIME type for the given file extension.
//& type: auto
/**
* @testcase 			ITc_mime_type_get_mime_type_for_file
* @since_tizen 			4.0
* @author            	SRID(samuel.peter)
* @reviewer         	SRID(manoj.g2)
* @type 				auto
* @description			Gets the MIME type for the given file.
* @scenario				Get mime-type using mime_type_get_mime_type_for_file
* @apicovered			mime_type_get_mime_type_for_file
* @passcase				if mime_type_get_mime_type_for_file successful
* @failcase				if mime_type_get_mime_type_for_file fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_mime_type_get_mime_type_for_file(void)
{
	START_TEST;

	char *pszMimeType = NULL;
	char *pszPath = NULL;
	char *pszOutMimeType = "image/jpeg";
	int nSize = 0;
	int nRet = 0;

	pszPath = MimeTypeGetDataPath(SAMPLE_FILE_PATH);
	if ( NULL == pszPath)
	{
		FPRINTF("[Line : %d][%s] MimeTypeGetDataPath failed, error returned\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = mime_type_get_mime_type_for_file(pszPath, &pszMimeType);
	PRINT_RESULT_CLEANUP(MIME_TYPE_ERROR_NONE, nRet, "mime_type_get_mime_type_for_file", MimeTypeGetError(nRet),FREE_MEMORY(pszPath));
	CHECK_HANDLE(pszMimeType,"mime_type_get_mime_type_for_file");

	nSize = sizeof(pszOutMimeType);
	if(strncmp(pszMimeType, pszOutMimeType, nSize) != 0)
	{
		FPRINTF("[Line : %d][%s] incorrect mime_type returned.\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszMimeType);
		FREE_MEMORY(pszPath);
		return 1;
	}

	FPRINTF("[Line : %d][%s] mime_type : %s\\n", __LINE__, API_NAMESPACE, pszMimeType);
	FREE_MEMORY(pszMimeType);
	FREE_MEMORY(pszPath);

	return 0;
}
/** @} */ //end of itc-mime-type
/** @} */ //end of itc-mime-type-testcases
