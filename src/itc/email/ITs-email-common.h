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
#ifndef _ITS_EMAIL_COMMON_H_
#define _ITS_EMAIL_COMMON_H_

//Add test package related includes here

#include "tct_common.h"

#include <app.h>
#include <email.h>

#include <glib.h>
#include <glib-object.h>

/** @addtogroup itc-email
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE				"EMAIL_ITC"
#define TIMEOUT_CB					30000
#define PATH_LEN					1024

#define ACCOUNT_USERNAME			sbrcsrbdtest@gmail.com
#define ACCOUNT_PASSWORD			root080233
#define EMAILSUBJECT				"Sample E-Mail Subject"
#define EMAILBODY					"Sample E-Mail Body Text"
#define EMAILADDRESS				"sbrcsrbdtest@gmail.com"		//password : root080233
#define IMAGE_NAME					"Image_01.jpg"

#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define WIFI_FEATURE				"http://tizen.org/feature/network.wifi"
#define EMAIL_FEATURE               "http://tizen.org/feature/email"   //Mail feature ACR 992


#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
        if(g_eEmailNotSupported)\
        {\
        	FPRINTF("[Line : %d][%s] Feature =%s  not supported  :success ", __LINE__, API_NAMESPACE,EMAIL_FEATURE);\
            return 0;\
        }\
        else if (g_eEmailMismatch)\
        {\
	        FPRINTF("[Line : %d][%s] Precondition of email feature=%s:Mismatch,failure  ", __LINE__, API_NAMESPACE,EMAIL_FEATURE);\
            return 1;\
        }\
        if ( !g_bEmailCreation )\
        {\
            FPRINTF("[Line : %d][%s] Precondition of email message handle creation failed. So leaving test ", __LINE__, API_NAMESPACE);\
            return 1;\
        }\
}

#define RUN_POLLING_LOOP {\
	g_pEmailMainLoop = g_main_loop_new(NULL, false);\
	nEmailTimeoutId = g_timeout_add(TIMEOUT_CB, EmailTimeout, g_pEmailMainLoop);\
	g_main_loop_run(g_pEmailMainLoop);\
	g_source_remove(nEmailTimeoutId);\
	g_pEmailMainLoop = NULL;\
}

GMainLoop *g_pEmailMainLoop;
email_h g_hEmail;

bool g_bIsEmailSendFeatureSupported;
bool g_bEmailCreation;
bool g_bCallbackOccurred;
bool g_bEmailSentSuccess;

bool g_eEmailNotSupported;
bool g_eEmailMismatch;


// Maps error enums to string values
char* EmailGetError(int nRet);

// Maps recipient type enums to string values
char* EmailGetRecipientType(int nRecipient);

// Create email message without attachment
bool CreateEmailMessageWithoutAttachment(email_h email);

// Create email message with attachment
bool CreateEmailMessageWithAttachment(email_h email);

// Get the path to application data directory
char* EmailGetDataPath(char *pszFileName);

/** @} */

#endif  //_ITS_EMAIL_COMMON_H_
