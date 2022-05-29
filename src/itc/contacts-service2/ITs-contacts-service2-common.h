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
#ifndef _ITS_CONTACTS_SERVICE2_COMMON_H_
#define _ITS_CONTACTS_SERVICE2_COMMON_H_

#include "tct_common.h"

//Add test package related includes here
#include <contacts.h>
#include <glib.h>
#include <app.h>
#include <telephony.h>

/** @addtogroup itc-contacts-service2
*  @ingroup itc
*  @{
*/
//Add helper function declarations here

bool g_bContactsServiceCreation;
bool g_bCallbackHit;
bool g_bCallbackReturnValue;
GMainLoop *g_pContactsServiceMainLoop;
contacts_record_h g_hRecordFirst;
contacts_record_h g_hRecordSecond;
contacts_record_h g_hRecordFront;
contacts_record_h g_hRecordBack;
int g_nFirstRecordId;
int g_nFirstPersonId;
int g_nFirstContactId;
int g_nSecondRecordId;
int g_nSecondPersonId;
int g_nSecondContactId;
int g_nFrontRecordId;
int g_nFrontPersonId;
int g_nFrontContactId;
int g_nBackRecordId;
int g_nBackPersonId;
int g_nBackContactId;
int g_nPersonId;
contacts_record_h g_hFirstProfileRecord;
contacts_record_h g_hSecondProfileRecord;
contacts_record_h g_hFrontProfileRecord;
contacts_record_h g_hBackProfileRecord;
int g_nGroupId;
contacts_record_h g_hGroupRecord;
bool g_bIsConnected;
bool g_bIsContactFeatureSupported;
bool g_bContactFeatureMismatch;

#define API_NAMESPACE           "CONTACTS_SERVICE2_ITC"
#define PATH_LEN				1024
#define MINCOUNT				1
#define TESTSTRINGSIZE			120*sizeof(char)
#define VCFPATH					"/tmp/Test.vcf"
#define IMAGEPATH				"icon.png"
#define RINGTONEPATH			"TestRingtone.mp3"
#define TIMEOUT_CB				10000
#define SIZE					1
#define SLEEP_TIME				5
#define TELEPHONY_FEATURE		"http://tizen.org/feature/network.telephony"
#define CONTACT_FEATURE			"http://tizen.org/feature/contact"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if(!g_bIsContactFeatureSupported && !g_bContactFeatureMismatch)\
{\
	FPRINTF("[Line : %d] [contacts-service_ITC] contact feature not supported, Leaving test\\n", __LINE__);\
	return 0;\
}\
	if ( !g_bContactsServiceCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of contacts_service failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	g_pContactsServiceMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pContactsServiceMainLoop);\
	g_main_loop_run(g_pContactsServiceMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pContactsServiceMainLoop = NULL;\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

gboolean Timeout(gpointer data);
char* ContactsServiceGetError(int nRet);
bool ContactsServiceConnect(void);
bool ContactsServiceDisconnect(void);
char* ContactsServiceGetEnumForInt(int nRet);
char* ContactsServiceGetEnumForStr(int nRet);
char* ContactsServiceGetEnumForOperator(int nRet);
char* ContactsServiceGetEnumForDisplayOrder(int nRet);
char* ContactsServiceGetEnumForSortingOrder(int nRet);
char* ContactsServiceGetEnumForPersonProperty(int nRet);
char* ContactsServiceGetEnumForUsageType(int nRet);
bool CreateVcard(void);
bool ContactsServiceCreateAndInsertGroupRecord();
bool ContactsServiceCreateAndInsertRecord(int *nRecordId, int *nContactId, int *nPersonId, contacts_record_h *hProfileRecord, contacts_record_h *hRecord, const char *pszNumber, const char *pszName);
bool ContactsServiceCreateAndInsertRecordSdn(contacts_record_h *hProfileRecord);
bool ContactsServiceGetDataPath(char* pPath);
bool ContactsServiceAppendToAppDataPath(char* pInputPath, char* pFinalPath);
/** @} */ 
#endif  //_ITS_CONTACTS_SERVICE_COMMON_H_
