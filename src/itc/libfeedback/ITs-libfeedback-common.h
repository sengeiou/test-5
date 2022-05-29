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
#ifndef _ITS_FEEDBACK_COMMON_H_
#define _ITS_FEEDBACK_COMMON_H_

#include "tct_common.h"
#include <feedback.h>

/** @addtogroup itc-feedback
*  @ingroup itc
*  @{
*/

//Add test package related includes here
#define LOG							100	
#define MAX_BUFFER 					1000
#define API_NAMESPACE 				"FEEDBACK_ITC"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bFeedbackInit )\
	{\
		FPRINTF("[Line : %d][%s] Precondition of Feedback Initialization failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

typedef struct {
	feedback_type_e eType;
	char* szType;
} stFeedbackType;

typedef struct {
	feedback_pattern_e ePattern;
	char* szPattern;
} stFeedbackPattern;

//Add helper function declarations here
char *FeedbackGetError(int nRet);

/** @} */

#endif  //_ITS_FEEDBACK_COMMON_H_
