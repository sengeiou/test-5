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
#ifndef _ITS_BUNDLE_COMMON_H_
#define _ITS_BUNDLE_COMMON_H_

#include "tct_common.h"

#include "bundle.h"
#include <glib.h>

/** @addtogroup itc-bundle
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE		"BUNDLE_ITC"
#define KEY1				"key1"
#define KEY1_VALUE			"myvalue"
#define KEY2				"key2"
#define KEY2_VALUE			"myvalue2"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bBundleCreation )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of bundle create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

/**
* @function 		BundleGetType
* @description	 	Maps Types of given values to string.
* @parameter		nRet : result code returned
* @return 			Type represented as string
*/
char* BundleGetType(int nRet);
/**
* @function 		BundleGetTypePropertyValue
* @description	 	Maps Types of given values to string.
* @parameter		nRet : result code returned
* @return 			Type represented as string
*/
char* BundleGetTypePropertyValue(int nRet);
/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* BundleGetError(int nRet);
/** @} */
#endif  //_ITS_BUNDLE_COMMON_H_
