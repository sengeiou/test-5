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
#ifndef _ITS_FIDO_CLIENT_COMMON_H_
#define _ITS_FIDO_CLIENT_COMMON_H_

//Add test package related includes here
#include "tct_common.h"
#include "fido_uaf_types.h"
#include <glib.h>
#include "fido_uaf_authenticator.h"
#include "fido_uaf_client.h"
//#include "fido_uaf_version.h"



bool g_bFidoClientCreation;
GMainLoop *g_pMainLoop;
bool g_bFidoClientNotSupported;
 gboolean TimeoutFunction(gpointer data);



#define API_NAMESPACE		"FIDOCLIENT_ITC"
#define FIDOCLIENT_FEATURE			"http://tizen.org/feature/fido.uaf"
#define GMAINTIMEOUT                    10000
#define NUM_GET_TC_TYPE		14



/** @addtogroup itc-%{MODULE_NAME}
*  @ingroup itc
*  @{
*/
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bFidoClientNotSupported )\
	{\
	FPRINTF("[Line : %d][%s] Fidoclient feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	if ( !g_bFidoClientCreation )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of bundle create failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define RUN_POLLING_LOOP {\
    g_pMainLoop = g_main_loop_new(NULL, false);\
    nTimeoutId = g_timeout_add(GMAINTIMEOUT, TimeoutFunction, g_pMainLoop);\
    g_main_loop_run(g_pMainLoop);\
    g_source_remove(nTimeoutId);\
    g_pMainLoop = NULL;\
}

typedef enum
{
	TITLE = 0,
	AAID,
	DESCRIPTION,
	SCHEME,
	ALGORITHM,
	VERIFICATION_METHOD,
	KEY_PROTECTION,
	ATTACHMENT_HINT,
	IS_SECOND_FACTOR,
	TC_DISPLAY_TYPE,
	TC_DISPLAY,
	ICON,
	MATCHER_PROTECTION_METHOD,
	ATTESTATION,
	MAX_ENUM
}GET_TC_TYPE;

typedef struct key_value
{
	GET_TC_TYPE e_Get_TC_Type;
	bool bResult;
}KEY_VALUE;

KEY_VALUE stArr_Key_Value[NUM_GET_TC_TYPE];

//Add helper function declarations here
/**
* @function 		BundleGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* FidoClientGetError(int nRet);


/** @} */
#endif  //_ITS_FIDO_CLIENT_COMMON_H_
