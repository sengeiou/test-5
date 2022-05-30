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
#ifndef _ITS_SMARTCARD_COMMON_H_
#define _ITS_SMARTCARD_COMMON_H_

#include "tct_common.h"
#include <smartcard.h>

#define API_NAMESPACE		"SMARTCARD_ITC"
#define SE_FEATURE			"http://tizen.org/feature/network.secure_element"
#define SE_UICC_FEATURE		"http://tizen.org/feature/network.secure_element.uicc"
#define SE_ESE_FEATURE		"http://tizen.org/feature/network.secure_element.ese"

//Add test package related includes here


bool g_bIsUICCSupported;
bool g_bIsESESupported;
bool g_bIsSmartcardSupported;
bool g_bIsFeatureMismatched;
bool g_bIsServiceInitialized;
bool g_bIsReadersAvailable;

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_CHECK_INITIALIZE {\
	START_TEST;\
	if ( g_bIsFeatureMismatched ) {\
		FPRINTF("[Line : %d][%s] Feature Mismatch Error\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	if ( !g_bIsSmartcardSupported ) {\
		FPRINTF("[Line : %d][%s] Feature Unsupported\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
	if ( !g_bIsServiceInitialized ) {\
		FPRINTF("[Line : %d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

#define START_TEST_CHECK_READERS {\
	START_TEST_CHECK_INITIALIZE;\
	if ( !g_bIsReadersAvailable ) {\
		FPRINTF("[Line : %d][%s] Precondition Failed\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
}

//Add helper function declarations here

char* SmartcardGetError(int nRet);
#endif  //_ITS_SMARTCARD_COMMON_H_
