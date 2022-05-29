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
#ifndef _ITS_nfc_COMMON_H_
#define _ITS_nfc_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"
#include <pthread.h>
#include <nfc.h>
#include <app_manager.h>
#include <stdlib.h>
#include <app.h>
#include <glib-object.h>
#include <glib-2.0/glib.h>

/** @addtogroup itc-nfc
* @ingroup		itc
* @{
*/

#define SHORT_DELAY					 1
#define LONG_DELAY					 2
#define COUNTER 					30
#define MICROSECONDS_PER_SECOND		1000000
#define TEST_TESTNFCLIENT_APPID		"org.tizen.testnfclient"
#define SEAPPIDHEXVALUE				"6f72672e74697a656e2e746573746e66636c69656e74" // Hex value of org.tizen.testnfclient
#define ENCODE_TEXT  				"TEST"
#define ENCODE_TYPE_UTF8  			"en-US"
#define ENCODE_TYPE_UTF16  			"ko-KR"
#define URI							"http://www.google.com"
#define SERVICE_ACCESS_NAME			"urn:nfc:sn:snep"
#define SERVICE_ACCESS_POINT		4
#define NFC_FEATURE                 "http://tizen.org/feature/network.nfc"
#define NFC_CARD_EMULATION_FEATURE  "http://tizen.org/feature/network.nfc.card_emulation"
#define API_NAMESPACE				"NFC_ITC"
#define NFC_HCE_FEATURE  			"http://tizen.org/feature/network.nfc.card_emulation.hce"
#define NFC_TAG_FEATURE             "http://tizen.org/feature/network.nfc.tag"
#define NFC_P2P_FEATURE             "http://tizen.org/feature/network.nfc.p2p"

bool g_bNFCTestPrecondition;
bool g_bIsSupportedNFC;
bool g_bNFCNotSupported;
bool g_bMismatch;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bNFCNotSupported )\
{\
	FPRINTF("[Line : %d][%s]  [Not supported]  system_info_get_platform_bool and nfc_manager_is_supported returned Unsupported feature capability for NFC\\n", __LINE__, API_NAMESPACE);\
	return 0;\
}\
	if ( g_bMismatch )\
{\
	FPRINTF("[Line : %d][%s] system_info_get_platform_bool and nfc_manager_is_supported returned different feature for NFC so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
	if ( !g_bNFCTestPrecondition )\
{\
	FPRINTF("[Line : %d][%s] Precondition API failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define START_TEST_CARD_EMUL_CHECK {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

nfc_ndef_message_h g_hMessage;
nfc_ndef_record_h g_hRecord;
bool NFCCreateMessageRecordHandle(void);
bool NFCCreateRecordText(nfc_encode_type_e encode_type, int nEnumCounter);
void NFCDestroyText(nfc_encode_type_e encode_type, int nEnumCounter);
bool NFCCreateUri(void);
char* NFCTagFilterEnumString(int nRet);
char* NFCSeTypeEnumString(int nRet);
char* NFCGetError(int nRet);
char* NFCGetTnfEnumString(int nRet);
char* NFCGetEncodeEnumString(int nRet);
bool LaunchApp (char *pszRemoteAppId);
char* AppControlGetError(int nRet);
void TerminateApp();
/** @} */ //end of itc-nfc

#endif  //_ITS_nfc_COMMON_H_