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
#ifndef _ITS_MEDIA_KEY_COMMON_H_
#define _ITS_MEDIA_KEY_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include "media_key.h"

/** @addtogroup itc-media-key
* @ingroup		itc
* @{
*/

#define API_NAMESPACE			"MEDIA_KEY_ITC"
#define WAIT_CALLBACK			5

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

//Add helper function declarations here

char* Media_KeyGetError(int nRet);

/** @} */ //end of itc-media-key

#endif  //_ITS_MEDIA_KEY_COMMON_H_