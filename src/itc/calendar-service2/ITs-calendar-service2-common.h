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
#ifndef _ITS_CALENDAR_SERVICE2_COMMON_H_
#define _ITS_CALENDAR_SERVICE2_COMMON_H_

#include <calendar.h>
#include "tct_common.h"
#include <glib-object.h>
#include <glib-2.0/glib.h>
#include <contacts.h>
#include <app.h>
#include <telephony.h>

/** @addtogroup itc-calendar-service2
*  @ingroup itc
*  @{
*/

#define VCAL_FILE_PATH				"/tmp/calendar.ics"				//This is an output file required for generating .ics file
#define SIZE						1
#define MAX_ROW						20
#define MAX_COL						100
#define MAX_URI_COUNT				15
#define URI_COUNT_FOR_DB			11
#define URI_COUNT_FOR_DB_BY_VERSION 2
#define PASS						0
#define FAIL						1
#define API_NAMESPACE				"CALENDAR_SERVICE2_ITC"
#define CALENDAR_FEATURE "http://tizen.org/feature/calendar"

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bCalendarMismatch )\
{\
        FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by calendar_connect() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
        return 1;\
}\
        else if ( g_bCalendarNotSupported )\
{\
        FPRINTF("[Line : %d] [%s] calendar feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
        return 0;\
}\
	else if ( !g_bCalendarConnect )\
{\
	FPRINTF("[Line : %d][%s] Precondition of connecting to calendar service failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define START_TEST_NO_CHECK {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if ( Handle == NULL )\
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
	FreeResource;\
	return 1;\
}\
}

bool g_bCalendarConnect;
bool g_bIsConnected;
bool g_bCalendarIssupportedFeature;
bool g_bCalendarNotSupported;
bool g_bCalendarMismatch;
char* CalendarServiceGetError(int nRet);
int CreateCalendarRecord(calendar_record_h *record);
int CreateCalendarRecordInsertInDb(calendar_record_h *record, int *nRecordId);
int CreateCalendarList(calendar_list_h *phList);
int CreateQueryWithFilter(calendar_query_h *query, calendar_filter_h *filter);
void GetViewURI(char szArr[MAX_ROW][MAX_COL]);
char* CalendarFilterOperator(int nRet);
void GetViewURIforDB(char szArr[MAX_ROW][MAX_COL]);
void GetViewURIforDBByVersion(char szArr[MAX_ROW][MAX_COL]);
gboolean Timeout_Function(gpointer data);
time_t get_utime(int y, int m, int d, int h, int n, int s);
int CalendarCheckContact(int nContactId, int nMonth, int nMday);
int ContactsServiceCreateAndInsertRecord(int *nRecordId,int nDateTime, int nType, char *szLabel);
char* ContactsServiceGetError(int nRet);
int ModifyContact(int nContactId, int nDateTime);
/** @} */ 

#endif  //_ITS_CALENDAR_SERVICE2_COMMON_H_
