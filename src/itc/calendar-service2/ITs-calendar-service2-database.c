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

//& set: CalendarService2

static GMainLoop *g_pMainLoop;
static bool g_nCheckCb = false;

/**
* @function 		ITs_calendar_service_startup
* @description	 	Called before each test, connects to the calendar service
* @parameter		NA
* @return 			NA
*/
void ITs_calendar_service2_database_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Calendar_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCalendarIssupportedFeature = TCTCheckSystemInfoFeatureSupported(CALENDAR_FEATURE, API_NAMESPACE);
        g_bCalendarConnect = false;
        int nRet = calendar_connect();
        if ( false == g_bCalendarIssupportedFeature)
        {
                if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
                {
                        g_bCalendarMismatch = true;
                }
                else
                {
                        g_bCalendarNotSupported = true;
                }
                return;
        }
	if ( nRet != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to connect to the calendar service, error returned = %s\\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRet));
		g_bCalendarConnect = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Connected to the calendar service successfully\\n", __LINE__, API_NAMESPACE);
		g_bCalendarConnect = true;
	}
	return;
}

/**
* @function 		ITs_calendar_service_cleanup
* @description	 	Called after each test, disconnects to the calendar service
* @parameter		NA
* @return 			NA
*/
void ITs_calendar_service2_database_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Calendar_Service_p\\n", __LINE__, API_NAMESPACE);
#endif

	int nRet = calendar_disconnect();
	if ( nRet != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to disconnect to the calendar service, error returned = %s\\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRet));
	}
	return;
}

/**
* @function 		CalenderServiceRecordChangeCallback
* @description	 	callback for calendar record change
* @parameter		view_uri : view uri, user_data : user data
* @return 			NA
*/
static void CalenderServiceRecordChangeCallback(const char *view_uri, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Record change callback\\n", __LINE__, API_NAMESPACE);
	g_nCheckCb = true;
	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
}


/** @addtogroup itc-calendar-service2-testcases
*  @brief 		Integration testcases for module calendar-service2
*  @ingroup 	itc-calendar-service2
*  @{
*/

//& purpose:	Insert and delete a record to the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_insert_delete_record_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts and delete a record to the calendar database
* @scenario				Create a record by calendar_record_create\n
*						Inserts a record to the calendar database by calendar_db_insert_record\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_db_insert_record,  calendar_db_delete_record and calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_insert_record and calendar_db_delete_record and a valid record id from calendar_db_insert_record
* @failcase				If target APIs calendar_db_insert_record or calendar_db_delete_record fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_insert_delete_record_p(void)
{
	START_TEST;

	int nEventId = -1;
	calendar_record_h record = NULL;

	// Precondition
	if ( CreateCalendarRecord(&record) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_db_insert_record(record, &nEventId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true));

	if (nEventId == -1)
	{
		FPRINTF("[Line : %d][%s] calendar_db_insert_record failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(record, true);
		return 1;
	}

	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true));

	//Postcondition
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Insert and delete multiple records as list to the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_insert_delete_records_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts and delete a record to the calendar database
* @scenario				Create multiple records by calendar_record_create\n
*						Create calendar list by calendar_list_create\n
*						Add multiple records in the calendar list\n
*						Inserts calendar list to the calendar database by calendar_db_insert_records\n
*						Delete calendar list from the calendar database by calendar_db_delete_records\n
*						Delete calendar list by calendar_list_destroy
* @apicovered			calendar_db_insert_records,  calendar_db_delete_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_insert_records and calendar_db_delete_records and a valid record ids from calendar_db_insert_records
* @failcase				If target APIs calendar_db_insert_records or calendar_db_delete_records fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_insert_delete_records_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;
	int *pnIds = NULL;
	int nCount = 0;

	// Preconditions
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_db_insert_records(hList, &pnIds, &nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	PRINT_RESULT_CLEANUP(3, nCount, "calendar_db_insert_records", "Output parameter doesn't match the set value", calendar_list_destroy(hList, true)); // Three records created in CreateCalendarList

	CHECK_HANDLE_CLEANUP(pnIds, "calendar_db_insert_records", calendar_list_destroy(hList, true));

	nRetVal = calendar_db_delete_records(_calendar_event._uri, pnIds, nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	// Postconditions
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	FREE_MEMORY(pnIds);
	return 0;
}

//& purpose:	Gets a record from the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_record_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a record from the calendar database
* @scenario				Create a record by calendar_record_create\n
*						Inserts a record to the calendar database by calendar_db_insert_record\n
*						Get a record from calendar database by calendar_db_get_record\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_db_get_record, calendar_db_delete_record and calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_update_record
* @failcase				If target API calendar_db_update_record fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_record_p(void)
{
	START_TEST;

	int nEventId = 0;
	calendar_record_h record = NULL;
	calendar_record_h getRecord = NULL;

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nEventId) == FAIL )
	{
		return 1;
	}

	// Target API
	int nRetVal = calendar_db_get_record(_calendar_event._uri, nEventId, &getRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	CHECK_HANDLE_CLEANUP(getRecord, "calendar_db_get_record", calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	//Postconditions
	// destroy records
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(getRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	// delete record from database
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Retrieves all records as a list from db
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_all_records_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all records as a list from db
* @scenario				Retrieves all records as a list by giving start index and the number of records to be retrieved
* @apicovered			calendar_db_get_all_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_get_all_records and list returned is not NULL
* @failcase				If target API calendar_db_get_all_records fails or list returned is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_all_records_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 1;//set to 1 for  _calendar_event._uri
	calendar_list_h list = NULL;
	int nOffset = 0;
	int nLimit = 2;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURIforDB(szURI);
	int nEventId = 0;
	calendar_record_h record = NULL;
	
	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nEventId) == FAIL )
	{
		return 1;
	}

			// Target APIs
	nRetVal = calendar_db_get_all_records(szURI[nURICount], nOffset, nLimit, &list);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_all_records", CalendarServiceGetError(nRetVal));

	CHECK_HANDLE(list, "calendar_db_get_all_records");
	
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	// delete record from database
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));
	
	//Postcondition
	nRetVal = calendar_list_destroy(list, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	list = NULL;
	
	return 0;
}

//& purpose:	Updates a record in the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_update_record_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Updates a record in the calendar database
* @scenario				Create a record by calendar_record_create\n
*						Inserts a record to the calendar database by calendar_db_insert_record\n
*						Updates a record in the calendar database by calendar_db_update_record\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_db_update_record, calendar_db_get_record , calendar_record_set_str, calendar_db_delete_record and calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_update_record
* @failcase				If target API calendar_db_update_record fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_update_record_p(void)
{
	START_TEST;

	char *pszUpdateString = "Tizen Test";
	int nEventId = 0;
	calendar_record_h record = NULL;
	calendar_record_h updateRecord = NULL;

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nEventId) == FAIL )
	{
		return 1;
	}

	// get record
	int nRetVal = calendar_db_get_record(_calendar_event._uri, nEventId, &updateRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// update record
	nRetVal = calendar_record_set_str(updateRecord, _calendar_event.summary, pszUpdateString);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_record_destroy(updateRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// Target API
	nRetVal = calendar_db_update_record(updateRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_update_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_record_destroy(updateRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	//Postconditions
	// destroy records
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(updateRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	// delete record from database
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Update multiple records in the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_update_records_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Updates a record in the calendar database
* @scenario				Create a record by calendar_record_create\n
*						Inserts a record to the calendar database by calendar_db_insert_record\n
*						Get a record from calendar database by calendar_db_get_record\n
*						Update the record and add it in calendar list\n
*						Update the calender list in the calendar database by calendar_db_update_records\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_db_update_records, calendar_db_get_record, calendar_record_set_str, calendar_db_delete_record and calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_update_records
* @failcase				If target API calendar_db_update_records fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_update_records_p(void)
{
	START_TEST;

	int nEventId = 0;
	char *pszUpdateString = "Tizen Test";
	calendar_record_h record = NULL;
	calendar_record_h updateRecord = NULL;
	calendar_list_h list = NULL;

	// Preconditions
	// create list
	int nRetVal = calendar_list_create(&list);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_create", CalendarServiceGetError(nRetVal));

	// create and insert record
	if ( CreateCalendarRecordInsertInDb(&record, &nEventId) == FAIL )
	{
		return 1;
	}

	// get record
	nRetVal = calendar_db_get_record(_calendar_event._uri, nEventId, &updateRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// update record
	nRetVal = calendar_record_set_str(updateRecord, _calendar_event.summary, pszUpdateString);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true); calendar_record_destroy(updateRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// add record to list
	nRetVal = calendar_list_add(list, updateRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true); calendar_record_destroy(updateRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// Target API
	nRetVal = calendar_db_update_records(list);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_update_records", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true); calendar_record_destroy(updateRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	//Postconditions
	// destroy records
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(updateRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	// delete record from database
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Retrieve records with the given calendar database version
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_changes_by_version_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieve records with the given calendar database version
* @scenario				Get the db version by calendar_db_get_current_version\n
*						Retrieve records for given db version by calendar_db_get_changes_by_version\n
*						Destroy calendar list retrieved by calendar_list_destroy
* @apicovered			calendar_db_get_changes_by_version, calendar_db_get_current_version, calendar_list_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_get_changes_by_version and list returned is not NULL
* @failcase				If target API calendar_db_get_changes_by_version fails or list returned is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_changes_by_version_p(void)
{
	START_TEST;

	int nURICount = 1;
	calendar_list_h list = NULL;
	int nGivenVersion = 1;
	int nCurrentVersion = -1;

	char szURI[MAX_ROW][MAX_COL];
	GetViewURIforDBByVersion(szURI);
	int nEventID =0;
	
	// Target APIs
	int nRetVal = calendar_db_get_changes_by_version(_calendar_event._uri, nEventID, nGivenVersion, &list, &nCurrentVersion);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_changes_by_version", CalendarServiceGetError(nRetVal));

	CHECK_HANDLE(list, "calendar_db_get_changes_by_version");
	if ( nCurrentVersion == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_get_changes_by_version failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		calendar_list_destroy(list, true);
		return 1;
	}
	
	//Postconditions
	nRetVal = calendar_list_destroy(list, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Retrieves changed exception records since the given calendar database version
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_changes_exception_by_version_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieve records with the given calendar database version
* @scenario				Create a record and insert in db\n
*						Retrieve records for given db version by calendar_db_get_changes_exception_by_version\n
*						Destroy calendar list retrieved by calendar_list_destroy
* @apicovered			calendar_db_get_changes_exception_by_version, calendar_db_get_current_version and calendar_list_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_get_changes_exception_by_version and list returned is not NULL
* @failcase				If target API calendar_db_get_changes_exception_by_version fails or list returned is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_changes_exception_by_version_p(void)
{
	START_TEST;

	calendar_list_h list = NULL;
	int nGivenVersion = 1;
	int nEventId = 1;
	int nCurrentVersion = 0;
	int nEventID_F = 0;
	
	int nClone_ID = 0;
	calendar_record_h hGet_event = NULL;
	calendar_record_h hClone = NULL;	
	calendar_record_h event = NULL;
	 
	int nRetVal = calendar_record_create(_calendar_event._uri, &event);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(event, "calendar_record_create");

	 char buf[256] = {0};
	 snprintf(buf, sizeof(buf), "Test %ld", time(NULL));
	 nRetVal = calendar_record_set_str(event, _calendar_event.summary, buf);
	 PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));	

	 calendar_time_s st = {0};
	 st.type = CALENDAR_TIME_UTIME;
	 st.time.utime = get_utime(2010, 1, 5, 0, 0, 0);
	 
	  nRetVal = calendar_record_set_caltime(event, _calendar_event.start_time, st);
	  PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_caltime", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	

	 calendar_time_s et = {0};
	 et.type = CALENDAR_TIME_UTIME;
	 et.time.utime = st.time.utime + 3600;
	 nRetVal = calendar_record_set_caltime(event, _calendar_event.end_time, et);
	 PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_caltime", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));

	nRetVal = calendar_record_set_int(event, _calendar_event.freq, CALENDAR_RECURRENCE_DAILY);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	
	nRetVal = calendar_record_set_int(event, _calendar_event.range_type, CALENDAR_RANGE_COUNT);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	
	nRetVal = calendar_record_set_int(event, _calendar_event.count, 10);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	 
	nRetVal = calendar_db_insert_record(event, &nEventID_F);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	
	
	nRetVal = calendar_db_get_record(_calendar_event._uri, nEventID_F, &hGet_event);	
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true));
	CHECK_HANDLE(hGet_event, "calendar_db_get_record");
	

	nRetVal = calendar_record_clone(hGet_event, &hClone);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_clone", CalendarServiceGetError(nRetVal),calendar_record_destroy(event, true);calendar_record_destroy(hGet_event, true));
	 
	nRetVal = calendar_record_destroy(hGet_event, true);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal),calendar_record_destroy(hClone, true));

	nRetVal = calendar_record_set_str(hClone, _calendar_event.summary, "exception");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal),calendar_record_destroy(hClone, true));
	
	nRetVal = calendar_record_set_int(hClone, _calendar_event.original_event_id, nEventID_F);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal),calendar_record_destroy(hClone, true));
	 
	nRetVal = calendar_record_set_str(hClone, _calendar_event.recurrence_id, "20100106000000Z");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_str", CalendarServiceGetError(nRetVal),calendar_record_destroy(hClone, true));

	nRetVal = calendar_db_insert_record(hClone, &nClone_ID);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal),calendar_record_destroy(hClone, true));
	
	nRetVal = calendar_record_destroy(hClone, true);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));
		
	// Target API
	nRetVal = calendar_db_get_changes_exception_by_version(_calendar_event._uri, nEventID_F, nCurrentVersion, &list);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_changes_exception_by_version", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(list, "calendar_db_get_changes_exception_by_version");
	
	// destroy list
	nRetVal = calendar_list_destroy(list, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Get count of records for a specific view
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_count_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Get count of records for a specific view
* @scenario				Get count of records in db for a specific view by calendar_db_get_count
* @apicovered			calendar_db_get_count
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_get_count
* @failcase				If target API calendar_db_get_count fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_count_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 0;
	int nCount = -1;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURIforDB(szURI);
	int nTotalURICount = URI_COUNT_FOR_DB;

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target API
		nRetVal = calendar_db_get_count(szURI[nURICount], &nCount);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_count", CalendarServiceGetError(nRetVal));
		if ( nCount == -1 )
		{
			FPRINTF("[Line : %d][%s] calendar_db_get_count failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		nCount = -1;
	}
	return 0;
}

//& purpose:	Gets records count with a query handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_count_with_query_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets records count with a query handle
* @scenario				Creates a query handle\n
*						Creates a filter and sets condition\n
*						Sets the filter\n
*						Gets records count with a query handle by calendar_db_get_count_with_query\n
*						Destroys the query handle and the filter
* @apicovered			calendar_db_get_count_with_query, calendar_filter_destroy, calendar_query_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_get_count_with_query and count is returned
* @failcase				If target APIs calendar_db_get_count_with_query fail or count is not returned or any precondition API fails.
* @precondition			Connects to the calendar service and creates a query handle, creates a filter and sets the filter
* @postcondition		Disconnects from the calendar service and destroys the query handle
*/
int ITc_calendar_db_get_count_with_query_p(void)
{
	START_TEST;

	int nCount = -1, nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_query_h query = NULL;
	calendar_filter_h filter = NULL;

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nRecordId) == FAIL )
	{
		return 1;
	}
	if ( CreateQueryWithFilter(&query, &filter) == FAIL )
	{
		calendar_record_destroy(record, true);
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
		return 1;
	}

	// Target API
	int nRetVal = calendar_db_get_count_with_query(query, &nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_count_with_query", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nRecordId);calendar_query_destroy(query);calendar_filter_destroy(filter));
	if ( nCount == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_get_count_with_query failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(record, true);
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
		calendar_query_destroy(query);
		calendar_filter_destroy(filter);
		return 1;
	}

	//Postconditions
	// remove record from db
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nRecordId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));

	// destroy filter
	nRetVal = calendar_filter_destroy(filter);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));

	// destroy query handle
	nRetVal = calendar_query_destroy(query);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));

	// destroy record
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Gets the current calendar database version
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_current_version_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieve records with the given calendar database version
* @scenario				Get the db version by calendar_db_get_current_version
* @apicovered			calendar_db_get_current_version
* @passcase				CALENDAR_ERROR_NONE and the db version returned by calendar_db_get_current_version
* @failcase				If target API calendar_db_get_current_version fails or doesn't return db version or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_current_version_p(void)
{
	START_TEST;
	int nDbVersion = -1;

	// Target API
	int nRetVal = calendar_db_get_current_version(&nDbVersion);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_current_version", CalendarServiceGetError(nRetVal));
	if ( nDbVersion == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_get_current_version failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose:	Gets the last change version of the database on the current connection
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_last_change_version_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieve records with the given calendar database version
* @scenario				Gets the last change version of the database on the current connection by calendar_db_get_last_change_version
* @apicovered			calendar_db_get_last_change_version
* @passcase				CALENDAR_ERROR_NONE and the last change db version returned by calendar_db_get_last_change_version
* @failcase				If target API calendar_db_get_last_change_version fails or doesn't return last change db version or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_get_last_change_version_p(void)
{
	START_TEST;
	int nLastDbVersion = -1;

	// Target API
	int nRetVal = calendar_db_get_last_change_version(&nLastDbVersion);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_last_change_version", CalendarServiceGetError(nRetVal));
	if ( nLastDbVersion == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_get_last_change_version failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	return 0;
}

//& purpose:	Retrieves records using query handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_get_records_with_query_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves records using query handle
* @scenario				Creates a query handle\n
*						Creates a filter and sets condition\n
*						Sets the filter\n
*						Gets records with a query handle by calendar_db_get_records_with_query\n
*						Destroys the query handle and the filter
* @apicovered			calendar_db_get_records_with_query, calendar_filter_destroy, calendar_query_destroy
* @passcase				CALENDAR_ERROR_NONE returned by  calendar_db_get_records_with_query and record list is returned
* @failcase				If target APIs calendar_db_get_records_with_query fail or record list is NULL or any precondition API fails.
* @precondition			Connects to the calendar service and creates a query handle, creates a filter and sets the filter
* @postcondition		Disconnects from the calendar service and destroys the query handle
*/
int ITc_calendar_db_get_records_with_query_p(void)
{
	START_TEST;

	int nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_query_h query = NULL;
	calendar_filter_h filter = NULL;
	calendar_list_h list = NULL;
	int nOffset = 0, nLimit = 2;

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nRecordId) == FAIL )
	{
		return 1;
	}
	if ( CreateQueryWithFilter(&query, &filter) == FAIL )
	{
		calendar_record_destroy(record, true);
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_db_get_records_with_query(query, nOffset, nLimit, &list);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_count_with_query", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nRecordId);calendar_query_destroy(query);calendar_filter_destroy(filter));
	CHECK_HANDLE_CLEANUP(list, "calendar_db_get_records_with_query", calendar_record_destroy(record, true);calendar_db_delete_record(_calendar_event._uri,nRecordId);calendar_query_destroy(query);calendar_filter_destroy(filter));

	//Postconditions
	// remove record from db
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nRecordId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));

	// destroy filter
	nRetVal = calendar_filter_destroy(filter);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));

	// destroy query handle
	nRetVal = calendar_query_destroy(query);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));

	// destroy record
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Replaces a record in the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_replace_record_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Replaces a record in the calendar database
* @scenario				Creates a record and insert in db\n
*						Create another record\n
*						replace inserted record with newly created record by calendar_db_replace_record\n
*						Delete inserted record from db\n
*						Destroy record handles
* @apicovered			calendar_db_replace_record, calendar_db_delete_record, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_replace_record
* @failcase				If target APIs calendar_db_replace_record fail or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_replace_record_p(void)
{
	START_TEST;

	int nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_record_h replaceRecord = NULL;

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nRecordId) == FAIL )
	{
		return 1;
	}
	if ( CreateCalendarRecord(&replaceRecord) == FAIL )
	{
		calendar_record_destroy(record, true);
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
		return 1;
	}

	// Target API
	int nRetVal = calendar_db_replace_record(replaceRecord, nRecordId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_replace_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true);calendar_record_destroy(replaceRecord, true);
	calendar_db_delete_record(_calendar_event._uri,nRecordId));

	//Postconditions
	// remove record from db
	nRetVal = calendar_db_delete_record(_calendar_event._uri,nRecordId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));

	// destroy records
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(replaceRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Replaces multiple records in the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_replace_records_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Replaces a record in the calendar database
* @scenario				Creates multiple records and insert in db\n
*						replace inserted records with newly created records by calendar_db_replace_records\n
*						Delete inserted records from db\n
*						Destroy record handles
* @apicovered			calendar_db_replace_records, calendar_db_delete_records, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_replace_records
* @failcase				If target APIs calendar_db_replace_records fail or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_replace_records_p(void)
{
	START_TEST;

	calendar_record_h record1 = NULL;
	calendar_record_h record2 = NULL;
	calendar_list_h list = NULL;
	int nCount = 2;
	int nRecordId1 = -1,nRecordId2 = -1;
	int nIds[2] = {0};

	// Preconditions
	// Insert two records in db
	if ( CreateCalendarRecordInsertInDb(&record1, &nRecordId1) == FAIL )
	{
		return 1;
	}
	nIds[0] = nRecordId1;
	if ( CreateCalendarRecordInsertInDb(&record2, &nRecordId2) == FAIL )
	{
		calendar_record_destroy(record1, true);
		return 1;
	}
	nIds[1] = nRecordId2;

	// destroy records
	calendar_record_destroy(record1, true);
	calendar_record_destroy(record2, true);
	record1 = NULL;
	record2 = NULL;

	// create list to replace earlier records
	if ( CreateCalendarRecord(&record1) == FAIL )
	{
		calendar_db_delete_records(_calendar_event._uri, nIds, nCount);
		return 1;
	}
	if ( CreateCalendarRecord(&record2) == FAIL )
	{
		calendar_record_destroy(record1, true);
		calendar_db_delete_records(_calendar_event._uri, nIds, nCount);
		return 1;
	}
	// create list
	int nRetVal = calendar_list_create(&list);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(record1, true);calendar_record_destroy(record2, true);calendar_db_delete_records(_calendar_event._uri, nIds, nCount));
	// add records in the list
	nRetVal = calendar_list_add(list, record1);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal), calendar_record_destroy(record1, true);calendar_record_destroy(record2, true);calendar_db_delete_records(_calendar_event._uri, nIds, nCount));

	nRetVal = calendar_list_add(list, record2);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal), calendar_record_destroy(record1, true);calendar_record_destroy(record2, true);calendar_db_delete_records(_calendar_event._uri, nIds, nCount));


	// Target API
	nRetVal = calendar_db_replace_records(list, nIds, nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_replace_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(list, true);calendar_db_delete_records(_calendar_event._uri, nIds, nCount));

	//Postconditions
	// remove records from db
	nRetVal = calendar_db_delete_records(_calendar_event._uri, nIds, nCount);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_records", CalendarServiceGetError(nRetVal));

	// destroy list
	nRetVal = calendar_list_destroy(list, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Inserts a vcalendar stream to the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_insert_vcalendars_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Inserts a vcalendar stream to the calendar database
* @scenario				Create records and add them to calender list\n
*						Generate vcalendar stream from the calendar list\n
*						Insert vcalendar stream to the calendar database by calendar_db_insert_vcalendars\n
*						Destroy list
* @apicovered			calendar_db_insert_vcalendars, calendar_vcalendar_make_from_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_insert_vcalendars and record Ids are created along with count of records
* @failcase				If target API calendar_db_insert_vcalendars fails or record Ids are not created or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_insert_vcalendars_p(void)
{
	START_TEST;

	char *pszVcalStream = NULL;
	calendar_list_h hList = NULL;
	int *pnIds = NULL;
	int nCount = -1;

	//Precondition
	//create calendar list with records
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	//create vcal stream from list
	int nRetVal = calendar_vcalendar_make_from_records(hList, &pszVcalStream);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	CHECK_HANDLE_CLEANUP(pszVcalStream, "calendar_vcalendar_make_from_records", calendar_list_destroy(hList, true));

	// Target APIs
	nRetVal = calendar_db_insert_vcalendars(pszVcalStream, &pnIds, &nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_vcalendars", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true);FREE_MEMORY(pszVcalStream));

	CHECK_HANDLE_CLEANUP(pnIds, "calendar_db_insert_vcalendars", calendar_list_destroy(hList, true);FREE_MEMORY(pszVcalStream));

	if ( nCount == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_insert_vcalendars failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		calendar_list_destroy(hList, true);
		FREE_MEMORY(pszVcalStream);
		FREE_MEMORY(pnIds);
		return 1;
	}

	//Postcondition
	//destroy lists
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	FREE_MEMORY(pszVcalStream);
	FREE_MEMORY(pnIds);
	return 0;
}

//& purpose:	Replaces a vcalendar stream in the calendar database
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_replace_vcalendars_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Replaces a vcalendar stream in the calendar database
* @scenario				Create two calender lists\n
*						Generate two vcalendar streams one for inserting in db and other to replace first one in db\n
*						Insert vcalendar stream to the calendar database\n
*						Replace earlier vcalendar stream by other vcal stream in calendar database by calendar_db_replace_vcalendars\n
*						Destroy lists
* @apicovered			calendar_db_replace_vcalendars, calendar_vcalendar_make_from_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_replace_vcalendars and record Ids are created along with count of records
* @failcase				If target API calendar_db_replace_vcalendars fails or record Ids are not created or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_replace_vcalendars_p(void)
{
	START_TEST;

	char *pszVcalStreamIn = NULL;
	char *pszVcalStreamRplc = NULL;
	calendar_list_h hListIn = NULL;
	calendar_list_h hListRplc = NULL;
	int *pnIds = NULL;
	int nCount = -1;

	//Precondition
	//create calendar lists with records
	if ( CreateCalendarList(&hListIn) == FAIL )
	{
		return 1;
	}
	if ( CreateCalendarList(&hListRplc) == FAIL )
	{
		calendar_list_destroy(hListIn,true);
		return 1;
	}

	//create vcal streams from lists
	int nRetVal = calendar_vcalendar_make_from_records(hListIn, &pszVcalStreamIn);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true));

	CHECK_HANDLE_CLEANUP(pszVcalStreamIn, "calendar_vcalendar_make_from_records", calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true));

	nRetVal = calendar_vcalendar_make_from_records(hListRplc, &pszVcalStreamRplc);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true);FREE_MEMORY(pszVcalStreamIn));

	CHECK_HANDLE_CLEANUP(pszVcalStreamRplc, "calendar_vcalendar_make_from_records", calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true);FREE_MEMORY(pszVcalStreamIn));

	// insert vcal in db
	nRetVal = calendar_db_insert_vcalendars(pszVcalStreamIn, &pnIds, &nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true);FREE_MEMORY(pszVcalStreamIn);FREE_MEMORY(pszVcalStreamRplc));

	// Target APIs
	nRetVal = calendar_db_replace_vcalendars(pszVcalStreamRplc, pnIds, nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hListIn,true);calendar_list_destroy(hListRplc,true);FREE_MEMORY(pszVcalStreamIn);FREE_MEMORY(pszVcalStreamRplc);FREE_MEMORY(pnIds));

	//Postcondition
	//destroy lists
	nRetVal = calendar_list_destroy(hListIn,true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_list_destroy(hListRplc,true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	FREE_MEMORY(pszVcalStreamIn);
	FREE_MEMORY(pszVcalStreamRplc);
	FREE_MEMORY(pnIds);
	return 0;
}


//& purpose:	Registers a callback function to be invoked when a record changes and unregisters the callback function
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_add_remove_changed_cb_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback function to be invoked when a record changes and unregisters the callback function
* @scenario				Create and inserts a record to the calendar database\n
*						Registers a callback function to be invoked when a record changes by calendar_db_add_changed_cb\n
*						Updates a record in the calendar database by\n
*						Unregisters the callback function by calendar_db_remove_changed_cb\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_db_add_changed_cb, calendar_db_remove_changed_cb, calendar_db_update_record, calendar_db_delete_record, calendar_record_destroy, calendar_record_set_str, calendar_db_get_record
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_remove_changed_cb and calendar_db_remove_changed_cb and required callback function is hit
* @failcase				If target API calendar_db_remove_changed_cb fails or required callback function is not hit or any precondition API fails
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_add_remove_changed_cb_p(void)
{
	START_TEST;
	int nEventId = -1;
	calendar_record_h hRecord = NULL;
	calendar_record_h hUpdateRec = NULL;
	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);
	g_nCheckCb = false;

	// Preconditions
	// insert record in db
	if ( CreateCalendarRecordInsertInDb(&hRecord, &nEventId) == FAIL )
	{
		return 1;
	}

	// get record
	int nRetVal = calendar_db_get_record(_calendar_event._uri, nEventId, &hUpdateRec);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// update record
	nRetVal = calendar_record_set_str(hUpdateRec, _calendar_event.summary, "Tizen Native API Test");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hUpdateRec, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	// Target APIs
	nRetVal = calendar_db_add_changed_cb(_calendar_event._uri, CalenderServiceRecordChangeCallback, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hUpdateRec, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	nRetVal = calendar_db_update_record(hUpdateRec);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hUpdateRec, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	nTtimeoutId = g_timeout_add(2000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	if ( g_nCheckCb == false )
	{
		FPRINTF("[Line : %d][%s] calendar_db_add_changed_cb failed error =  callback is not hit\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(hRecord, true);
		calendar_record_destroy(hUpdateRec, true);
		calendar_db_delete_record(_calendar_event._uri,nEventId);
		return 1;
	}

	nRetVal = calendar_db_remove_changed_cb(_calendar_event._uri, CalenderServiceRecordChangeCallback, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hUpdateRec, true);calendar_db_delete_record(_calendar_event._uri,nEventId));

	//Postconditions
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(hUpdateRec, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_db_delete_record(_calendar_event._uri,nEventId);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_delete_record", CalendarServiceGetError(nRetVal));
	return 0;
}


//& purpose:	Clean record after sync
//& type  :		Auto
/**
* @testcase 			ITc_calendar_db_clean_after_sync_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Replaces a record in the calendar database
* @scenario				Creates a record and insert in db\n
*						Call calendar_db_clean_after_sync
*						Delete inserted record from db\n
*						Destroy record handles
* @apicovered			calendar_db_clean_after_sync, calendar_db_delete_record, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_db_clean_after_sync
* @failcase				If target APIs calendar_db_clean_after_sync fail or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_db_clean_after_sync_p(void)
{
	START_TEST;

	int nRecordId = -1;
	int nGivenVersion = -1;
	calendar_record_h record = NULL;

	int nRetVal = calendar_db_get_current_version(&nGivenVersion);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_get_current_version", CalendarServiceGetError(nRetVal));
	if ( nGivenVersion == -1 )
	{
		FPRINTF("[Line : %d][%s] calendar_db_get_current_version failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Preconditions
	nRetVal = calendar_record_create(_calendar_book._uri, &record);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_db_insert_record(record, &nRecordId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true));

	// Target API
	nRetVal = calendar_db_clean_after_sync(nRecordId, nGivenVersion);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_clean_after_sync", CalendarServiceGetError(nRetVal), calendar_record_destroy(record, true); calendar_db_delete_record(_calendar_event._uri,nRecordId));

	//Postconditions
	// destroy records
	nRetVal = calendar_record_destroy(record, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}


/**
* @function 		CalenderServiceDBChangeCallback
* @description	 	callback for calendar db change
* @parameter		uri : uri, user_data : user data
* @return 			NA
*/
void CalenderServiceDBChangeCallback(const char *uri, void *user_data)
{
	int ret = 0;
	int version = 0;
	int latest = 0;
	calendar_list_h list = NULL;
	
	g_nCheckCb = true;
	FPRINTF("[Line : %d][%s] callback triggered for calendar_db_add_changed_cb\\n", __LINE__, API_NAMESPACE);

	calendar_db_get_current_version(&version);
	calendar_db_get_changes_by_version(_calendar_event._uri, 0, version -1, &list, &latest);

	do {
		calendar_record_h event = NULL;
		ret = calendar_list_get_current_record_p(list, &event);

		int event_id = 0;
		int book_id = 0;
		int status = 0;
		int version = 0;
		ret = calendar_record_get_int(event, _calendar_updated_info.id, &event_id);
		ret = calendar_record_get_int(event, _calendar_updated_info.calendar_book_id, &book_id);
		ret = calendar_record_get_int(event, _calendar_updated_info.modified_status, &status);
		ret = calendar_record_get_int(event, _calendar_updated_info.version, &version);
		
		calendar_record_h clone = NULL;
		int clone_event_id = 0;
		int clone_book_id = 0;
		int clone_status = 0;
		int clone_version = 0;
		ret = calendar_record_clone(event, &clone);
		ret = calendar_record_get_int(clone, _calendar_updated_info.id, &clone_event_id);
		ret = calendar_record_get_int(clone, _calendar_updated_info.calendar_book_id, &clone_book_id);
		ret = calendar_record_get_int(clone, _calendar_updated_info.modified_status, &clone_status);
		ret = calendar_record_get_int(clone, _calendar_updated_info.version, &clone_version);
		calendar_record_destroy(clone, true);
	} while (CALENDAR_ERROR_NO_DATA != calendar_list_next(list));
	
	if (ret)
	{}
	calendar_list_destroy(list, true);
	g_main_loop_quit((GMainLoop *)user_data);
}



//& purpose:	Registers a callback function to be invoked when calendar db changes
//& type  :		Auto
/**
* @testcase 			ITc_calendar_add_changed_cb_p
* @since_tizen 			2.4
* @author            	SRID(satyajit.a)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback function to be invoked when calendar db changes
* @scenario				Registers a callback function through calendar_db_add_changed_cb API call\n
*						Create and inserts a record to the calendar database\n
*						Destroy the record\n
*						Unregisters the callback function by calendar_db_remove_changed_cb\n
* @apicovered			calendar_db_add_changed_cb, calendar_db_remove_changed_cb, calendar_record_create, calendar_record_set_caltime, calendar_db_insert_record, calendar_record_destroy
* @passcase				API calls returns success and callback function gets triggered.
* @failcase				If API calls return error or callback not triggered
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_add_changed_cb_p(void)
{
	int nRetVal = 0;
	int event_id = 0;
	int nTimeoutId = 0;
	calendar_record_h event = NULL;
	
	g_pMainLoop = g_main_loop_new(NULL, false);
	nRetVal = calendar_db_add_changed_cb(_calendar_event._uri, CalenderServiceDBChangeCallback, g_pMainLoop);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_add_changed_cb", CalendarServiceGetError(nRetVal));

	g_nCheckCb = false; //set callback flag to false
	
	//create record and insert into the db to trigger the callback
	nRetVal = calendar_record_create(_calendar_event._uri, &event);
	if( nRetVal != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] calendar_record_create API call failed, error returned = %s \\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRetVal));
		calendar_db_remove_changed_cb(_calendar_event._uri, CalenderServiceDBChangeCallback, g_pMainLoop);
		return 1;
	}
	
	calendar_time_s st = {0};
	st.type = CALENDAR_TIME_UTIME;
	st.time.utime = 1444122000; //sample value
	calendar_time_s et = {0};
	calendar_record_set_caltime(event, _calendar_event.start_time, st);
	et.type = CALENDAR_TIME_UTIME;
	et.time.utime = 1444125600; //sample value
	calendar_record_set_caltime(event, _calendar_event.end_time, et);
	
	nRetVal = calendar_db_insert_record(event, &event_id);
	if( nRetVal != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] calendar_db_insert_record API call failed, error returned = %s \\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRetVal));
		calendar_db_remove_changed_cb(_calendar_event._uri, CalenderServiceDBChangeCallback, g_pMainLoop);
		calendar_record_destroy(event, true);
		return 1;
	}

	calendar_record_destroy(event, true);

	nTimeoutId = g_timeout_add(5000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTimeoutId);
	
	//check callback flag
	if ( g_nCheckCb == false )
	{
		FPRINTF("[Line : %d][%s] calendar_db_add_changed_cb failed as callback is not hit\\n", __LINE__, API_NAMESPACE);
		calendar_db_remove_changed_cb(_calendar_event._uri, CalenderServiceDBChangeCallback, g_pMainLoop);
		return 1;
	}

	nRetVal = calendar_db_remove_changed_cb(_calendar_event._uri, CalenderServiceDBChangeCallback, g_pMainLoop);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_remove_changed_cb", CalendarServiceGetError(nRetVal));
	
	return 0;
}


/** @} */
/** @} */
