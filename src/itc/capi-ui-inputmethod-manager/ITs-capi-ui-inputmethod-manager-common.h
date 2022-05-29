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
#ifndef _ITS_INPUTMETHOD_MANAGER_COMMON_H_
#define _ITS_INPUTMETHOD_MANAGER_COMMON_H_

#include "tct_common.h"
#include "inputmethod_manager.h"
#include <glib.h>

/** @addtogroup itc-inputmethod-manager
* @ingroup		itc
* @{
*/

//Add test package related includes here
#define API_NAMESPACE			"INPUTMETHOD_MANAGER_ITC"
#define LEN						20

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test\\n", __LINE__, API_NAMESPACE);\
}

//Add helper function declarations here
char* InputmethodManagerGetError(int nRet);

/** @} */ //end of inputmethod-manager

#endif  //_ITS_INPUTMETHOD_MANAGER_COMMON_H_
