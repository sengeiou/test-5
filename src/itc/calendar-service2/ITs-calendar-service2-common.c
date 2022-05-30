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
#include "ITs-calendar-service2-common.h"

/** @addtogroup itc-calendar-service2
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		CalendarServiceGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* CalendarServiceGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case CALENDAR_ERROR_DB_FAILED:				szErrorVal = "CALENDAR_ERROR_DB_FAILED";				break;
	case CALENDAR_ERROR_DB_RECORD_NOT_FOUND:	szErrorVal = "CALENDAR_ERROR_DB_RECORD_NOT_FOUND";		break;
	case CALENDAR_ERROR_OUT_OF_MEMORY:			szErrorVal = "CALENDAR_ERROR_OUT_OF_MEMORY";			break;
	case CALENDAR_ERROR_INVALID_PARAMETER:		szErrorVal = "CALENDAR_ERROR_INVALID_PARAMETER";		break;
	case CALENDAR_ERROR_NO_DATA:				szErrorVal = "CALENDAR_ERROR_NO_DATA";					break;
	case CALENDAR_ERROR_NOW_IN_PROGRESS:		szErrorVal = "CALENDAR_ERROR_NOW_IN_PROGRESS";			break;
	case CALENDAR_ERROR_ALREADY_IN_PROGRESS:	szErrorVal = "CALENDAR_ERROR_ALREADY_IN_PROGRESS";		break;
	case CALENDAR_ERROR_NOT_PERMITTED:			szErrorVal = "CALENDAR_ERROR_NOT_PERMITTED";			break;
	case CALENDAR_ERROR_IPC:					szErrorVal = "CALENDAR_ERROR_IPC";						break;
	case CALENDAR_ERROR_FILE_NO_SPACE:			szErrorVal = "CALENDAR_ERROR_FILE_NO_SPACE";			break;
	case CALENDAR_ERROR_PERMISSION_DENIED :		szErrorVal = "CALENDAR_ERROR_PERMISSION_DENIED";		break;
	case CALENDAR_ERROR_SYSTEM :				szErrorVal = "CALENDAR_ERROR_SYSTEM";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		CreateCalendarRecord
* @description	 	Create a calendar record
* @parameter		calendar_record_h *record
* @return 			returns 0 in success and returns 1 in fail
*
*/ 
int CreateCalendarRecord(calendar_record_h *record)
{
	calendar_record_h event;
	int nRetVal = 0;
	// create a record
	nRetVal =  calendar_record_create(_calendar_event._uri, &event);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(event, "calendar_record_create");

	// set record summary
	nRetVal =  calendar_record_set_str(event, _calendar_event.summary, "TEST API");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal), calendar_record_destroy(event, true));

	*record = event;
	return 0;
}

/**
* @function 		CreateCalendarRecordInsertInDb
* @description	 	Create a calendar record and insert in db
* @parameter		calendar_record_h *record
* @return 			returns 0 in success and returns 1 in fail
*
*/ 
int CreateCalendarRecordInsertInDb(calendar_record_h *record, int *nRecordId)
{
	calendar_record_h event;
	int nRetVal = 0;
	int nEventId = 0;

	// create a record
	nRetVal =  calendar_record_create(_calendar_event._uri, &event);
	CHECK_HANDLE(event, "calendar_record_create");
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	// set record summary
	nRetVal =  calendar_record_set_str(event, _calendar_event.summary, "Meeting");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal), calendar_record_destroy(event, true));

	// insert record
	nRetVal = calendar_db_insert_record(event, &nEventId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(event, true));
	*record = event;
	*nRecordId = nEventId;
	return 0;
}

/**
* @function 		CreateCalendarList
* @description	 	Create a calendar list with multiple records
* @parameter		calendar_list_h *phList
* @return 			returns 0 in success and returns 1 in fail
*
*/ 
int CreateCalendarList(calendar_list_h *phList)
{
	int nRetVal = 0;

	calendar_record_h hRecord1 = NULL;
	calendar_record_h hRecord2 = NULL;
	calendar_record_h hRecord3 = NULL;
	calendar_list_h hList = NULL;

	// create records
	if ( CreateCalendarRecord(&hRecord1) == FAIL )
	{
		return FAIL;
	}
	if ( CreateCalendarRecord(&hRecord2) == FAIL )
	{
		return FAIL;
	}
	if ( CreateCalendarRecord(&hRecord3) == FAIL )
	{
		return FAIL;
	}

	// create list
	nRetVal = calendar_list_create(&hList);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_create", CalendarServiceGetError(nRetVal));

	// add records in list
	nRetVal =  calendar_list_add(hList,hRecord1);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal));

	nRetVal =  calendar_list_add(hList,hRecord2);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal));

	nRetVal =  calendar_list_add(hList,hRecord3);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal));

	*phList = hList;
	return 0;
}

/**
* @function 		CreateQueryWithFilter
* @description	 	Create a calendar query containing filter
* @parameter		calendar_query_h *query, calendar_filter_h *filter
* @return 			returns 0 in success and returns 1 in fail
*
*/ 
int CreateQueryWithFilter(calendar_query_h *query, calendar_filter_h *filter)
{
	calendar_query_h lQuery;
	calendar_filter_h lFilter;
	int nRetVal = 0;

	// create query handle
	nRetVal = calendar_query_create(_calendar_event._uri, &lQuery);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(lQuery, "calendar_query_create");

	// create filter
	nRetVal = calendar_filter_create(_calendar_event._uri, &lFilter);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal), calendar_query_destroy(lQuery));
	CHECK_HANDLE_CLEANUP(lFilter, "calendar_filter_create", calendar_query_destroy(lQuery));

	// add condition for string property
	nRetVal = calendar_filter_add_str(lFilter, _calendar_event.summary, CALENDAR_MATCH_FULLSTRING, "Meeting");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_str", CalendarServiceGetError(nRetVal), calendar_query_destroy(lQuery);calendar_filter_destroy(lFilter));

	// set filter in query
	nRetVal = calendar_query_set_filter(lQuery, lFilter);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_set_filter", CalendarServiceGetError(nRetVal), calendar_query_destroy(lQuery);calendar_filter_destroy(lFilter));

	*query = lQuery;
	*filter = lFilter;
	return 0;
}

/**
* @function 		GetViewURI
* @description	 	Store different view URI in 2d array
* @parameter		2d array
* @return 			None
*/
void GetViewURI(char szArr[MAX_ROW][MAX_COL])
{
	strncpy(szArr[0], _calendar_book._uri, MAX_COL-1);
	strncpy(szArr[1], _calendar_event._uri, MAX_COL-1);
	strncpy(szArr[2], _calendar_todo._uri, MAX_COL-1);
	strncpy(szArr[3], _calendar_timezone._uri, MAX_COL-1);
	strncpy(szArr[4], _calendar_attendee._uri, MAX_COL-1);
	strncpy(szArr[5], _calendar_alarm._uri, MAX_COL-1);
	strncpy(szArr[6], _calendar_extended_property._uri, MAX_COL-1);
	strncpy(szArr[7], _calendar_updated_info._uri, MAX_COL-1);
	strncpy(szArr[8], _calendar_event_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[9], _calendar_todo_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[10], _calendar_event_calendar_book_attendee._uri, MAX_COL-1);
	strncpy(szArr[11], _calendar_instance_utime_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[12], _calendar_instance_localtime_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[13], _calendar_instance_utime_calendar_book_extended._uri, MAX_COL-1);
	strncpy(szArr[14], _calendar_instance_localtime_calendar_book_extended._uri, MAX_COL-1);
}

/**
* @function 		CalendarFilterOperator
* @description	 	Maps Filter operator enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* CalendarFilterOperator(int nRet)
{
	char *szFilterOp = NULL;

	switch ( nRet )
	{
	case CALENDAR_FILTER_OPERATOR_AND:		szFilterOp = "CALENDAR_FILTER_OPERATOR_AND";		break;
	case CALENDAR_FILTER_OPERATOR_OR:		szFilterOp = "CALENDAR_FILTER_OPERATOR_OR";			break;
	case CALENDAR_FILTER_OPERATOR_MAX:		szFilterOp = "CALENDAR_FILTER_OPERATOR_MAX";		break;
	default:								szFilterOp = "Unknown Filter Operator";				break;
	}
	return szFilterOp;
}

/**
* @function 		GetViewURIforDB
* @description	 	Store different view URI in 2d array
* @parameter		2d array
* @return 			None
*/
void GetViewURIforDB(char szArr[MAX_ROW][MAX_COL])
{
	strncpy(szArr[0], _calendar_book._uri, MAX_COL-1);
	strncpy(szArr[1], _calendar_event._uri, MAX_COL-1);
	strncpy(szArr[2], _calendar_todo._uri, MAX_COL-1);
	strncpy(szArr[3], _calendar_timezone._uri, MAX_COL-1);
	strncpy(szArr[4], _calendar_attendee._uri, MAX_COL-1);
	strncpy(szArr[5], _calendar_alarm._uri, MAX_COL-1);
	strncpy(szArr[6], _calendar_extended_property._uri, MAX_COL-1);
	strncpy(szArr[7], _calendar_instance_utime_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[8], _calendar_instance_localtime_calendar_book._uri, MAX_COL-1);
	strncpy(szArr[9], _calendar_instance_utime_calendar_book_extended._uri, MAX_COL-1);
	strncpy(szArr[10], _calendar_instance_localtime_calendar_book_extended._uri, MAX_COL-1);
}


/**
* @function 		GetViewURIforDBByVersion
* @description	 	Store different view URI in 2d array
* @parameter		2d array
* @return 			None
*/
void GetViewURIforDBByVersion(char szArr[MAX_ROW][MAX_COL])
{
	strncpy(szArr[0], _calendar_event._uri, MAX_COL-1);
	strncpy(szArr[1], _calendar_todo._uri, MAX_COL-1);
}

/**
* @function 		Timeout_Function
* @description	 	calculating time
* @parameter		gpointer data
* @return 			None
*/

gboolean Timeout_Function(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

time_t get_utime(int y, int m, int d, int h, int n, int s)
{
	struct tm st = {0};
	st.tm_year = y - 1900;
	st.tm_mon = m - 1;
	st.tm_mday = d;
	st.tm_hour = h;
	st.tm_min = n;
	st.tm_sec = s;
	return mktime(&st);
}

/**
* @function 		ContactsServiceGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ContactsServiceGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CONTACTS_ERROR_OUT_OF_MEMORY:			szErrorVal = "CONTACTS_ERROR_OUT_OF_MEMORY";			break;
	case CONTACTS_ERROR_INVALID_PARAMETER:		szErrorVal = "CONTACTS_ERROR_INVALID_PARAMETER";		break;
	case CONTACTS_ERROR_FILE_NO_SPACE:			szErrorVal = "CONTACTS_ERROR_FILE_NO_SPACE";			break;
	case CONTACTS_ERROR_NO_DATA:				szErrorVal = "CONTACTS_ERROR_NO_DATA";					break;
	case CONTACTS_ERROR_PERMISSION_DENIED:		szErrorVal = "CONTACTS_ERROR_PERMISSION_DENIED";		break;
	case CONTACTS_ERROR_DB:						szErrorVal = "CONTACTS_ERROR_DB";						break;
	case CONTACTS_ERROR_DB_LOCKED:				szErrorVal = "CONTACTS_ERROR_DB_LOCKED";				break;
	case CONTACTS_ERROR_IPC_NOT_AVALIABLE:		szErrorVal = "CONTACTS_ERROR_IPC_NOT_AVALIABLE";		break;
	case CONTACTS_ERROR_IPC:					szErrorVal = "CONTACTS_ERROR_IPC";						break;
	case CONTACTS_ERROR_SYSTEM:					szErrorVal = "CONTACTS_ERROR_SYSTEM";					break;
	case CONTACTS_ERROR_INTERNAL:				szErrorVal = "CONTACTS_ERROR_INTERNAL";					break;
	default:									szErrorVal = "Unknown Error";							break;
	}

	return szErrorVal;
}

/**
* @function 		ContactsServiceCreateAndInsertRecord
* @description	 	Create a record and insert in DB
* @parameter		NA
* @return 			true if contact successfully added, else false
*/
int ContactsServiceCreateAndInsertRecord(int *nRecordId,int nDateTime, int nType, char *szLabel)
{
	contacts_record_h hMainRecord = NULL;
	contacts_record_h hNameRecord = NULL;
	contacts_record_h hNumberRecord = NULL;
	contacts_record_h hEventRecord = NULL;

	int nRet = contacts_record_create(_contacts_contact._uri, &hMainRecord);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet));
	CHECK_HANDLE(hMainRecord, "contacts_record_create");

	nRet = contacts_record_create(_contacts_number._uri, &hNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false));
	CHECK_HANDLE(hNumberRecord, "contacts_record_create");

	nRet = contacts_record_set_int(hNumberRecord, _contacts_number.type, CONTACTS_NUMBER_TYPE_CELL);  
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true));

	nRet = contacts_record_set_str(hNumberRecord, _contacts_number.number, "010-1234-5678");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.number, hNumberRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true));

	nRet = contacts_record_create(_contacts_name._uri, &hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true));
	CHECK_HANDLE(hNameRecord, "contacts_record_create");

	nRet = contacts_record_set_str(hNameRecord, _contacts_name.first, "Birth");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true));

	nRet = contacts_record_set_str(hNameRecord, _contacts_name.last, "day");
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.name, hNameRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true));

	nRet = contacts_record_create(_contacts_event._uri, &hEventRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_create", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true));
	CHECK_HANDLE(hEventRecord, "contacts_record_create");

	nRet = contacts_record_set_int(hEventRecord, _contacts_event.type, nType);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hEventRecord, true));
	if (CONTACTS_EVENT_TYPE_CUSTOM == nType)
	{
		nRet = contacts_record_set_str(hEventRecord, _contacts_event.label, szLabel);
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_str", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hEventRecord, true));
	}
	nRet = contacts_record_set_int(hEventRecord, _contacts_event.date, nDateTime);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hEventRecord, true));

	nRet = contacts_record_add_child_record(hMainRecord, _contacts_contact.event, hEventRecord);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_add_child_record", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hEventRecord, true));

	nRet = contacts_db_insert_record(hMainRecord, nRecordId);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_db_insert_record", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hEventRecord, true));

	nRet = contacts_record_destroy(hEventRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet),contacts_record_destroy(hNameRecord, true);contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hMainRecord, false));

	nRet = contacts_record_destroy(hNameRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet),contacts_record_destroy(hNumberRecord, true);contacts_record_destroy(hMainRecord, false));

	nRet = contacts_record_destroy(hNumberRecord, true);
	PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet),contacts_record_destroy(hMainRecord, false));

	nRet = contacts_record_destroy(hMainRecord, false);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	hMainRecord = NULL;

	return 0;
}

/**
* @function 		CalendarCheckContact
* @parameter		int nContactId, int nMonth, int nMday
* @return 			true else false
*/
int CalendarCheckContact(int nContactId, int nMonth, int nMday)
{   
	calendar_filter_h hFilter = NULL;
	calendar_query_h hQuery = NULL;
	calendar_list_h hList = NULL;

	int nRet = calendar_filter_create(_calendar_event._uri, &hFilter);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRet, "calendar_filter_create", CalendarServiceGetError(nRet));

	nRet = calendar_filter_add_int(hFilter, _calendar_event.person_id,CALENDAR_MATCH_EQUAL, nContactId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_filter_add_int", CalendarServiceGetError(nRet), calendar_filter_destroy(hFilter));

	nRet = calendar_query_create(_calendar_event._uri, &hQuery);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_query_create", CalendarServiceGetError(nRet), calendar_filter_destroy(hFilter));

	nRet = calendar_query_set_filter(hQuery, hFilter);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_query_set_filter", CalendarServiceGetError(nRet), calendar_query_destroy(hQuery);calendar_filter_destroy(hFilter));

	nRet = calendar_db_get_records_with_query(hQuery, 0, 0, &hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_db_get_records_with_query", CalendarServiceGetError(nRet),calendar_query_destroy(hQuery);calendar_filter_destroy(hFilter));
	CHECK_HANDLE_CLEANUP(hList, "calendar_db_get_records_with_query",calendar_query_destroy(hQuery);calendar_filter_destroy(hFilter));

	nRet = calendar_filter_destroy(hFilter);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRet, "calendar_filter_destroy", CalendarServiceGetError(nRet));

	nRet = calendar_query_destroy(hQuery);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRet, "calendar_query_destroy", CalendarServiceGetError(nRet));

	int nCount = 0;
	nRet = calendar_list_get_count(hList,&nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_list_get_count", CalendarServiceGetError(nRet),calendar_list_destroy(hList, true));
	FPRINTF("[Line : %d][%s] nCount(%d)\\n", __LINE__, API_NAMESPACE, nCount);
	if (nCount <= 0)
		return 0;

do {
	calendar_record_h hEvent = NULL;
	nRet = calendar_list_get_current_record_p(hList, &hEvent);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_list_get_current_record_p", CalendarServiceGetError(nRet),calendar_list_destroy(hList, true));
	calendar_time_s st = {0};
	nRet = calendar_record_get_caltime(hEvent, _calendar_event.start_time, &st);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRet, "calendar_record_get_caltime", CalendarServiceGetError(nRet),calendar_list_destroy(hList, true));
	if (CALENDAR_TIME_LOCALTIME == st.type)
		FPRINTF("[Line : %d][%s] Pass\\n", __LINE__, API_NAMESPACE);
	if (st.time.date.month == nMonth)
		FPRINTF("[Line : %d][%s] nMonth(%d)\\n", __LINE__, API_NAMESPACE, nMonth);
	if (st.time.date.mday == nMday)
		FPRINTF("[Line : %d][%s] nMday(%d)\\n", __LINE__, API_NAMESPACE, nMday);
} while (0);

	nRet = calendar_list_destroy(hList, true);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRet, "calendar_list_destroy", CalendarServiceGetError(nRet));

	return 0;
} 

/**
* @function 		ModContact
* @parameter		int nContactId, int nDateTime
* @return 			true else false
*/
 int ModifyContact(int nContactId, int nDateTime)   
{   
	contacts_record_h hContact = NULL;
	contacts_record_h hEvent = NULL;

	int nRet = contacts_db_get_record(_contacts_contact._uri, nContactId, &hContact);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_get_record", ContactsServiceGetError(nRet));

	nRet = contacts_record_get_child_record_at_p(hContact, _contacts_contact.event, 0, &hEvent);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_get_child_record_at_p", ContactsServiceGetError(nRet));

	nRet = contacts_record_set_int(hEvent, _contacts_event.date, nDateTime);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_set_int", ContactsServiceGetError(nRet));

	nRet = contacts_db_update_record(hContact);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_db_update_record", ContactsServiceGetError(nRet));

	nRet = contacts_record_destroy(hContact, true);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_record_destroy", ContactsServiceGetError(nRet));

	return 0;
} 

/** @} */ 
