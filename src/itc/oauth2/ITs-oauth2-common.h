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
#ifndef _ITS_OAUTH2_COMMON_H_
#define _ITS_OAUTH2_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include <oauth2.h>

/** @addtogroup itc-oauth2
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE						"OAUTH2_ITC"

bool g_bIsRequestHandleCreated;

#define START_TEST_NO_CHECK {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bIsRequestHandleCreated ) {\
		FPRINTF("[Line : %d][%s] Precondition failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

//Add helper function declarations here

char* Oauth2InfoGetError(int nRet);
char* Oauth2GrantType(oauth2_grant_type_e nRet);
char* Oauth2ResponseType(oauth2_response_type_e nRet);
char* Oauth2GetAuthType(oauth2_client_authentication_type_e nRet);

/** @} */
#endif  //_ITS_OAUTH2_COMMON_H_
