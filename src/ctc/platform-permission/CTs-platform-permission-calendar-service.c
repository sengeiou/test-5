#include "CTs-platform-permission-common.h"

#include <calendar.h>
#include "tct_common.h"
#include <glib-object.h>
#include <glib-2.0/glib.h>

#define PASS						0
#define FAIL						1
#define SIZE						1
#define MAX_ROW						20
#define MAX_COL						100
#define URI_COUNT_FOR_DB			11

static bool g_nCheckCb = false;
bool g_bCalendarConnect;

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
	case CALENDAR_ERROR_NONE:					szErrorVal = "CALENDAR_ERROR_NONE";				break;
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

/**
* @function 		GetViewURIforDB
* @description	 	Store different view URI in 2d array
* @parameter		2d array
* @return 			None
*/

void GetViewURIforDB(char szArr[MAX_ROW][MAX_COL])
{
	strncpy(szArr[0], _calendar_book._uri, strlen(_calendar_book._uri)+1);
	strncpy(szArr[1], _calendar_event._uri, strlen(_calendar_event._uri)+1);
	strncpy(szArr[2], _calendar_todo._uri, strlen(_calendar_todo._uri)+1);
	strncpy(szArr[3], _calendar_timezone._uri, strlen(_calendar_timezone._uri)+1);
	strncpy(szArr[4], _calendar_attendee._uri, strlen(_calendar_attendee._uri)+1);
	strncpy(szArr[5], _calendar_alarm._uri, strlen(_calendar_alarm._uri)+1);
	strncpy(szArr[6], _calendar_extended_property._uri, strlen(_calendar_extended_property._uri)+1);
	strncpy(szArr[7], _calendar_instance_utime_calendar_book._uri, strlen(_calendar_instance_utime_calendar_book._uri)+1);
	strncpy(szArr[8], _calendar_instance_localtime_calendar_book._uri, strlen(_calendar_instance_localtime_calendar_book._uri)+1);
	strncpy(szArr[9], _calendar_instance_utime_calendar_book_extended._uri, strlen(_calendar_instance_utime_calendar_book_extended._uri)+1);
	strncpy(szArr[10], _calendar_instance_localtime_calendar_book_extended._uri, strlen(_calendar_instance_localtime_calendar_book_extended._uri)+1);
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
	CHECK_HANDLE(lFilter, "calendar_filter_create");

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
	/*	nRetVal = calendar_db_insert_record(event, &nEventId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(event, true));
	*/
	
	*record = event;
	*nRecordId = nEventId;
	return 0;
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
* @function         CTs_platform_permission_CalendarService_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_CalendarService_startup(void)
{
    struct stat stBuff;
    if ( stat(ERR_LOG, &stBuff) == 0 )
    {
	if (remove(ERR_LOG))
	{
		FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
	}
    }

#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_CalendarService_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
	int nRet = calendar_connect();
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
* @function         CTs_platform_permission_CalendarService_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_CalendarService_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_CalendarService_p\\n", __LINE__, API_NAMESPACE);
#endif
	int nRet = calendar_disconnect();
	if ( nRet != CALENDAR_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Unable to disconnect to the calendar service, error returned = %s\\n", __LINE__, API_NAMESPACE, CalendarServiceGetError(nRet));
	}
	return;
}


//& purpose:Checking tizen.org/privilege/calendar.write privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_record
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Inserts and delete a record to the calendar database			
* @apicovered		calendar_db_insert_record,  calendar_db_delete_record and calendar_record_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_record(void)
{
	START_TEST;
	int nEventId = -1;
	calendar_record_h record = NULL;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	// Precondition
	if ( CreateCalendarRecord(&record) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRet = calendar_db_insert_record(record, &nEventId);	
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "calendar_db_insert_record", CalendarServiceGetError(nRet),calendar_db_delete_record(_calendar_event._uri,nEventId); calendar_record_destroy(record, true));
	
	calendar_db_delete_record(_calendar_event._uri,nEventId);
	calendar_record_destroy(record, true);
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.write privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Insert and delete multiple records as list to the calendar database		
* @apicovered		calendar_db_insert_records,  calendar_db_delete_records and calendar_record_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_records(void)
{
	START_TEST;
	calendar_list_h hList = NULL;
	int *pnIds = NULL;
	int nCount = 0;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	// Preconditions
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_db_insert_records(hList, &pnIds, &nCount);
	if(nRetVal == CALENDAR_ERROR_NONE)
	{
		calendar_db_delete_records(_calendar_event._uri, pnIds, nCount);
		calendar_list_destroy(hList, true);
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.write privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_vcalendars
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Inserts a vcalendar stream to the calendar database
* @apicovered		calendar_db_insert_vcalendars, calendar_vcalendar_make_from_records
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_insert_vcalendars(void)
{
	START_TEST;
	char *pszVcalStream = NULL;
	calendar_list_h hList = NULL;
	int *pnIds = NULL;
	int nCount = -1;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	//Precondition
	//create calendar list with records
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	//create vcal stream from list
	int nRetVal = calendar_vcalendar_make_from_records(hList, &pszVcalStream);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	// Target APIs
	nRetVal = calendar_db_insert_vcalendars(pszVcalStream, &pnIds, &nCount);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_insert_vcalendars", CalendarServiceGetError(nRetVal),calendar_list_destroy(hList, true); FREE_MEMORY(pszVcalStream);FREE_MEMORY(pnIds));
	
	calendar_list_destroy(hList, true);
	FREE_MEMORY(pszVcalStream);
	FREE_MEMORY(pnIds);
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.write privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_replace_record
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Replaces a record in the calendar database
* @apicovered		calendar_db_replace_record, calendar_db_delete_record, calendar_record_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_replace_record(void)
{
	START_TEST;
	int nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_record_h replaceRecord = NULL;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

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
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_replace_record", CalendarServiceGetError(nRetVal),calendar_db_delete_record(_calendar_event._uri,nRecordId);calendar_record_destroy(replaceRecord, true);calendar_record_destroy(record, true));
	
	calendar_db_delete_record(_calendar_event._uri,nRecordId);
	calendar_record_destroy(replaceRecord, true);
	calendar_record_destroy(record, true);
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.write privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_replace_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Replaces a record in the calendar database
* @apicovered		calendar_db_replace_records, calendar_db_delete_records, calendar_record_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarWrite_calendar_db_replace_records(void)
{
	START_TEST;
	calendar_record_h record1 = NULL;
	calendar_record_h record2 = NULL;
	calendar_list_h list = NULL;
	int nCount = 2;
	int nRecordId1 = -1,nRecordId2 = -1;
	int nIds[2] = {0};
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

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
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_replace_records", CalendarServiceGetError(nRetVal), calendar_record_destroy(record1, true);calendar_record_destroy(record2, true);calendar_db_delete_records(_calendar_event._uri, nIds, nCount);calendar_list_destroy(list, true););

	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_add_changed_cb
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Registers a callback function to be invoked when calendar db changes
* @apicovered		calendar_db_add_changed_cb
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_add_changed_cb(void)
{
	START_TEST;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }
	
	int nRetVal = calendar_db_add_changed_cb(_calendar_event._uri, CalenderServiceRecordChangeCallback, NULL);
	if( nRetVal == CALENDAR_ERROR_NONE)
	{
		// nTtimeoutId = g_timeout_add(2000, Timeout_Function, g_pMainLoop);
		// g_main_loop_run(g_pMainLoop);
		// g_source_remove(nTtimeoutId);
		FPRINTF("[Line : %d][%s] %s inside ERROR NONE passed\\n", __LINE__, API_NAMESPACE, "calendar_db_add_changed_cb");
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_add_changed_cb", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_all_records
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieves all records as a list from db
* @apicovered		calendar_db_get_all_records
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_all_records(void)
{
	START_TEST;
	
	int nRetVal = -1, nURICount = 0;
	calendar_list_h list = NULL;
	int nOffset = 0;
	int nLimit = 2;

	char szURI[MAX_ROW][MAX_COL];
	GetViewURIforDB(szURI);
	int nTotalURICount = URI_COUNT_FOR_DB;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target APIs
		nRetVal = calendar_db_get_all_records(szURI[nURICount], nOffset, nLimit, &list);
		if(nRetVal == CALENDAR_ERROR_NONE)
		{
			calendar_list_destroy(list, true);
			list = NULL;
		}
		PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_all_records", CalendarServiceGetError(nRetVal),calendar_list_destroy(list, true););
	}		
	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_current_version
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieves calendar database version
* @apicovered		calendar_db_get_current_version
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_current_version(void)
{
	START_TEST;	
	int nGivenVersion = -1;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	//Precondition
	int nRetVal = calendar_db_get_current_version(&nGivenVersion);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_current_version", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_last_change_version
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieve records with the given calendar database version
* @apicovered		calendar_db_get_current_version
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_last_change_version(void)
{
	START_TEST;	
	int nLastDbVersion = -1;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	// Target API
	int nRetVal = calendar_db_get_last_change_version(&nLastDbVersion);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_last_change_version", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_records_with_query
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieves records using query handle
* @apicovered		calendar_db_get_records_with_query
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_records_with_query(void)
{
	START_TEST;	
	
	int nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_query_h query = NULL;
	calendar_filter_h filter = NULL;
	calendar_list_h list = NULL;
	int nOffset = 0, nLimit = 2;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	// Preconditions
	if ( CreateCalendarRecordInsertInDb(&record, &nRecordId) == FAIL )
	{
		return 1;
	}
	CHECK_HANDLE(record, "CreateCalendarRecordInsertInDb");
	
	if ( CreateQueryWithFilter(&query, &filter) == FAIL )
	{
		calendar_record_destroy(record, true);
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
		return 1;
	}
	CHECK_HANDLE(filter, "CreateQueryWithFilter");
	
	// Target APIs
	int nRetVal = calendar_db_get_records_with_query(query, nOffset, nLimit, &list);
	if(nRetVal == CALENDAR_ERROR_NONE)
	{
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
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
	
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_records_with_query", CalendarServiceGetError(nRetVal));
	
	calendar_db_delete_record(_calendar_event._uri,nRecordId);
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


//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_count_with_query
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets records count with a query handle
* @apicovered		calendar_db_get_count_with_query
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_count_with_query(void)
{
	START_TEST;	
	
	int nCount = -1, nRecordId = -1;
	calendar_record_h record = NULL;
	calendar_query_h query = NULL;
	calendar_filter_h filter = NULL;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

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
	if(nRetVal == CALENDAR_ERROR_NONE)
	{
		calendar_db_delete_record(_calendar_event._uri,nRecordId);
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
	
	}
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_count_with_query", CalendarServiceGetError(nRetVal));
	
	calendar_db_delete_record(_calendar_event._uri,nRecordId);
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


//& purpose:Checking tizen.org/privilege/calendar.read privilege
//& type: auto
/**
* @testcase			CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_count
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Get count of records for a specific view
* @apicovered		calendar_db_get_count
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_CalendarService_PrivilegeCalendarRead_calendar_db_get_count(void)
{
	START_TEST;	
	
	int nRetVal = -1, nURICount = 0;
	int nCount = -1;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURIforDB(szURI);
	int nTotalURICount = URI_COUNT_FOR_DB;
	bool bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_CALENDAR, bIsSupported, API_NAMESPACE);
	if ( !bIsSupported )
        {
                FPRINTF("[Line : %d][%s] [%s]is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_CALENDAR);
                return 0;
        }

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target API
		nRetVal = calendar_db_get_count(szURI[nURICount], &nCount);
		PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRetVal, "calendar_db_get_count", CalendarServiceGetError(nRetVal));		
	}
	return 0;
}
