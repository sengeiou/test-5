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
#ifndef _ITS_KEY_MANAGER_COMMON_H__
#define _ITS_KEY_MANAGER_COMMON_H__

#include "tct_common.h"

#include <ckmc/ckmc-manager.h>
#include <ckmc/ckmc-type.h>
#include <ckmc/ckmc-error.h>

#include <app.h>
#include <pthread.h>

/** @addtogroup itc-key-manager
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"KEY_MANAGER_ITC"
#define PATH			 			"certificate.crt"
#define PATHPFX						"signer.p12"
#define PASSPHRASEPFX 				"1234"
#define PATH_LEN					1024

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_HANDLE(Handle, API) {\
	if ( Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
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

FILE *g_fpLog;

char* RSA_PUB_KEY_PEM;

char* CERT_PEM;

char* CRY_RSA_PRI_KEY;

char* CRY_CERT;

char* CERT_CHAIN1;

char* CERT_CHAIN2;

char *RSA_PRIKEY;

char *RSA_PRIKEY_PASS;

char *TEST_ROOT_CA;

char *TEST_IM_CA;

char *TEST_LEAF_CERT;

char *RSA_PUBKEY;

char* KeyMngrGetError(int nRet);
void LoadPkcs12(ckmc_pkcs12_s **pkcs12_bundle, int *nRetVal);
void SaveKey(char* alias, int *nRetVal);
void SaveCertificate(char* alias, int *nRetVal);
void SaveData(const char* alias, int *nRetVal);
void RemoveAlias(char* alias);
bool KeyManagerGetDataPath(char* pAppDataPath);
bool KeyManagerAppendToAppDataPath(char* pInputPath, char* pFinalPath);

/** @} */

#endif  //_ITS_KEY_MANAGER_COMMON_H_

