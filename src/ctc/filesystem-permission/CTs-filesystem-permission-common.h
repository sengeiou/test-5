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
#ifndef _CTS_FILESYSTEM_PERMISSION_COMMON_H_
#define _CTS_FILESYSTEM_PERMISSION_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include <storage.h>
#include <errno.h>

/** @addtogroup ctc-filesystem-permission
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE			"FILESYSTEM_PERMISSION_CTC"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Create File
bool FilePermissionCreateFile(int nStorageID, storage_directory_e eStorageDirectory);

//Check if directory
bool IsPathValid(char *pszPath);

//Create Directory
bool FilePermissionCreateDirectory(int nStorageID, storage_directory_e eStorageDirectory);

//Print Error Message
char* StorageGetError(int nResult);

/** @} */ //end of ctc-filesystem-permission

#endif  //_CTS_FILESYSTEM_PERMISSION_COMMON_H_
