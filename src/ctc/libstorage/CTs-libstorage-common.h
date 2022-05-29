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
#ifndef _CTS_LIBSTORAGE_COMMON_H_
#define _CTS_LIBSTORAGE_COMMON_H_

//Add test package related includes here
#include "tct_common.h"

#include <sys/statvfs.h>
#include <storage.h> 

/** @addtogroup ctc-libstorage
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE			"LIBSTORAGE_CTC"
#define MAXVAL 					1024
#define SYSTEM_MEMORY 			300000		// preserved memory in bytes for system
#define MIN_INTERNAL_MEMORY		1073741824	// 1GB internal memory should have in device

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

bool FileClose(FILE *pFile);
bool FileRemove(char* pFilePath);
bool FileCopy(char *pszSrcFilePath, char  *pszDestFilePath);
char* StorageGetError(int nResult);
void AppendFileName(char *pszDirPath, char *pszTragetPath);
FILE *FileOpen(char *pszDirPath, char *pszTragetPath);
bool IsPathValid(char *pszPath);

/** @} */ //end of ctc-libstorage

#endif  //_CTS_LIBSTORAGE_COMMON_H_