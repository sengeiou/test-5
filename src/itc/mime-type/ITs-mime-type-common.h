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
#ifndef _ITS_MIME_TYPE_COMMON_H_
#define _ITS_MIME_TYPE_COMMON_H_

#include "tct_common.h"
#include <mime_type.h>
#include <app.h>

/** @addtogroup itc-mime-type
* @ingroup		itc
* @{
*/

#define API_NAMESPACE			"MIME_TYPE_ITC"
#define SAMPLE_FILE_PATH		"Tizen-logo-wallpaper.jpg"
#define PATH_LEN			1024
//Add test package related includes here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

char* MimeTypeGetError(int nRet);
bool FileUtilGetDataPath(char* pAppDataPath);
bool FileUtilAppendToAppDataPath(char* pInputPath, char* pFinalPath);
char* MimeTypeGetDataPath(char *pszFileName);

/** @} */ //end of itc-mime-type

#endif  //_ITS_MIME_TYPE_COMMON_H_
