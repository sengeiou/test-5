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

/**
* @function 		ITs_calendar_service_startup
* @description	 	Called before each test, connects to the calendar service
* @parameter		NA
* @return 			NA
*/
void ITs_calendar_service2_record_startup(void)
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
void ITs_calendar_service2_record_cleanup(void)
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

/** @addtogroup itc-calendar-service2-testcases
*  @brief 		Integration testcases for module calendar-service2
*  @ingroup 	itc-calendar-service2
*  @{
*/

//& purpose:	Adds and removes a child record from the parent record
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_add_remove_child_record_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds and removes a child record from the parent record
* @scenario				Create parent and child records\n
*						Adds child record in the parent record by calendar_record_add_child_record\n
* 						Removes child record from the parent record by calendar_record_remove_child_record\n
* 						Destroy records
* @apicovered			calendar_record_add_child_record, calendar_record_remove_child_record, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_add_child_record and calendar_record_remove_child_record.
* @failcase				If target APIs calendar_record_add_child_record or calendar_record_remove_child_record fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_add_remove_child_record_p(void)
{
	START_TEST;

	calendar_record_h parentRecord = NULL;
	calendar_record_h childRecord = NULL;

	//Precondition
	// create parent record
	int nRetVal = calendar_record_create(_calendar_event._uri, &parentRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	// create child record
	nRetVal = calendar_record_create(_calendar_alarm._uri, &childRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true));

	// Target APIs
	nRetVal = calendar_record_add_child_record(parentRecord, _calendar_event.calendar_alarm, childRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true);calendar_record_destroy(childRecord, true));

	nRetVal = calendar_record_remove_child_record(parentRecord, _calendar_event.calendar_alarm, childRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_remove_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true);calendar_record_destroy(childRecord, true));
	// Postcondition
	nRetVal = calendar_record_destroy(parentRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(childRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Gets the number of child records in a record
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_get_child_record_count_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the number of child records in a record
* @scenario				Create parent and child records\n
*						Adds child record in the parent record by calendar_record_add_child_record\n
* 						Gets the number of child records in a record by calendar_record_get_child_record_count\n
* 						Destroy records
* @apicovered			calendar_record_get_child_record_count, calendar_record_add_child_record, calendar_record_remove_child_record, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_get_child_record_count and count of child records
* @failcase				If target APIs calendar_record_get_child_record_count or count of child records is not returned or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_get_child_record_count_p(void)
{
	START_TEST;

	calendar_record_h parentRecord = NULL;
	calendar_record_h childRecord = NULL;
	unsigned int nCount = 0;

	//Precondition
	// create parent record
	int nRetVal = calendar_record_create(_calendar_event._uri, &parentRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	// create child record
	nRetVal = calendar_record_create(_calendar_alarm._uri, &childRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true));

	// add child record in parent
	nRetVal = calendar_record_add_child_record(parentRecord, _calendar_event.calendar_alarm, childRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true);calendar_record_destroy(childRecord, true));

	// Target APIs

	nRetVal = calendar_record_get_child_record_count(parentRecord, _calendar_event.calendar_alarm, &nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_child_record_count", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true);calendar_record_destroy(childRecord, true));
	PRINT_RESULT_CLEANUP(1, nCount, "calendar_record_get_child_record_count", CalendarServiceGetError(nRetVal), calendar_record_destroy(parentRecord, true);calendar_record_destroy(childRecord, true));

	// Postcondition
	// remove child from parent
	nRetVal = calendar_record_remove_child_record(parentRecord, _calendar_event.calendar_alarm, childRecord);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_remove_child_record", CalendarServiceGetError(nRetVal));

	// destroy records
	nRetVal = calendar_record_destroy(parentRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(childRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Creates and destroys a calendar record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates and destroys a calendar record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_create and calendar_record_destroy and record handle is not NULL
* @failcase				If target APIs calendar_record_create or calendar_record_destroy fails or record handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_create_destroy_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 0;
	calendar_record_h hRecord = NULL;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURI(szURI);
	int nTotalURICount = MAX_URI_COUNT;


	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target APIs
		nRetVal = calendar_record_create(szURI[nURICount], &hRecord);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(hRecord, "calendar_record_create");

		nRetVal = calendar_record_destroy(hRecord, true);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Makes a clone of a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_clone_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Makes a clone of a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Makes a clone of a record handle by calendar_record_clone\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_clone, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_clone and record handle is not NULL
* @failcase				If target APIs calendar_record_clone or record handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_clone_p(void)
{
	START_TEST;
	calendar_record_h hRecord = NULL;
	calendar_record_h hCloneRecord = NULL;

	//Precondition
	// create record
	if ( CreateCalendarRecord(&hRecord) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_record_clone(hRecord, &hCloneRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_clone", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));
	CHECK_HANDLE_CLEANUP(hCloneRecord, "calendar_record_clone", calendar_record_destroy(hRecord, true));

	// Postcondition
	// destroy records
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_destroy(hCloneRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Set and get a calendar_time_s value to a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_set_get_caltime_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a calendar_time_s value to a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Sets a calendar_time_s value to a record by calendar_record_set_caltime\n
*						Gets a calendar_time_s value from a record by calendar_record_get_caltime\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_set_caltime, calendar_record_get_caltime, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_set_caltime and calendar_record_get_caltime and calendar_time_s recieves value by get
* @failcase				If target APIs calendar_record_set_caltime or calendar_record_get_caltime fails or calendar_time_s doesn't recieve value by get or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_set_get_caltime_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	calendar_time_s stSetTime = {0}, stGetTime = {0};

	stSetTime.type = CALENDAR_TIME_UTIME;
	stSetTime.time.date.year = 2014;
	stSetTime.time.date.month = 06;
	stSetTime.time.date.mday = 26;

	//Precondition
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(hRecord, "calendar_record_create");

	// Target APIs
	nRetVal = calendar_record_set_caltime(hRecord, _calendar_event.start_time, stSetTime);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_caltime", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_get_caltime(hRecord, _calendar_event.start_time, &stGetTime);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_caltime", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	PRINT_RESULT_CLEANUP(stSetTime.time.date.mday, stGetTime.time.date.mday, "calendar_record_get_caltime", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Set and get a double value to a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_set_get_double_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a double value to a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Sets a double value to a record by calendar_record_set_double\n
*						Gets a double value from a record by calendar_record_get_double\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_set_double, calendar_record_get_double, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_set_double and calendar_record_get_double and double value is recieved
* @failcase				If target APIs calendar_record_set_double or calendar_record_get_double fails or double value is not recieved or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_set_get_double_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	double nSetVal = 0.5;
	double nGetVal = 0.0;

	//Precondition
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(hRecord, "calendar_record_create");

	// Target APIs
	nRetVal = calendar_record_set_double(hRecord, _calendar_event.latitude, nSetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_double", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_get_double(hRecord, _calendar_event.latitude, &nGetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_double", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	if ( nGetVal != nSetVal )
	{
		FPRINTF("[Line : %d][%s] calendar_record_get_double failed : output parameter doesn't match set value\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(hRecord, true);
		return 1;
	}

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Set and get a integer value to a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_set_get_int_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a integer value to a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Sets a integer value to a record by calendar_record_set_int\n
*						Gets a integer value from a record by calendar_record_get_int\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_set_int, calendar_record_get_int, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_set_int and calendar_record_get_int and integer value is recieved
* @failcase				If target APIs calendar_record_set_int or calendar_record_get_int fails or integer value is not recieved or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_set_get_int_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	int nSetVal = 2;
	int nGetVal = 0;

	//Precondition
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(hRecord, "calendar_record_create");

	// Target APIs
	nRetVal = calendar_record_set_int(hRecord, _calendar_event.count, nSetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_get_int(hRecord, _calendar_event.count, &nGetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_int", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	PRINT_RESULT_CLEANUP(nSetVal, nGetVal, "calendar_record_get_int", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Set and get a long long integer value to a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_set_get_lli_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a long long integer value to a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Sets a long long integer value to a record by calendar_record_set_lli\n
*						Gets a long long integer value from a record by calendar_record_get_lli\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_set_lli, calendar_record_get_lli, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_set_lli and calendar_record_get_lli and long long integer value is recieved
* @failcase				If target APIs calendar_record_set_lli or calendar_record_get_lli fails or long long integer value is not recieved or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_set_get_lli_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	long long int nSetVal = 1234567;
	long long int nGetVal = 0;

	//Precondition
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(hRecord, "calendar_record_create");

	// Target APIs
	nRetVal = calendar_record_set_lli(hRecord, _calendar_event.created_time, nSetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_lli", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_get_lli(hRecord, _calendar_event.created_time, &nGetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_lli", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	if ( nGetVal != nSetVal )
	{
		FPRINTF("[Line : %d][%s] calendar_record_get_lli failed : output parameter doesn't match set value\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(hRecord, true);
		return 1;
	}

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Set and get a string value to a record handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_set_get_str_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a string value to a record handle
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Sets a string value to a record by calendar_record_set_str\n
*						Gets a string value from a record by calendar_record_get_str\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_set_str, calendar_record_get_str, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_set_str and calendar_record_get_str and string value is recieved
* @failcase				If target APIs calendar_record_set_str or calendar_record_get_str fails or string value is not recieved or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_set_get_str_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	char* pszSetVal = "TIZEN NATIVE TC";
	char* pszGetVal = NULL;

	//Precondition
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(hRecord, "calendar_record_create");

	// Target APIs
	nRetVal = calendar_record_set_str(hRecord, _calendar_event.summary, pszSetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_lli", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_get_str(hRecord, _calendar_event.summary, &pszGetVal);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_lli", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	if ( strcmp(pszGetVal,pszSetVal) != 0 )
	{
		FPRINTF("[Line : %d][%s] calendar_record_get_str failed, error returned = Invalid output parameter\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(hRecord, true);
		return 1;
	}

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Gets a string pointer from a record
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_get_str_p_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a string pointer from a record
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Gets a string pointer from a record by calendar_record_get_str_p\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_get_str_p, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_get_str_p and a valid string pointer
* @failcase				If target APIs calendar_record_get_str_p or string pointer is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_get_str_p_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	char* pszStrPtr = NULL;

	//Precondition
	if ( CreateCalendarRecord(&hRecord) == FAIL )
	{
		return 1;
	}

	// Target API
	int nRetVal = calendar_record_get_str_p(hRecord, _calendar_event.summary,&pszStrPtr);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_str_p", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	CHECK_HANDLE_CLEANUP(pszStrPtr, "calendar_record_get_str_p", calendar_record_destroy(hRecord, true));

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Gets URI string from a record
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_get_uri_p_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets URI string from a record
* @scenario				Create a calendar record handle by calendar_record_create\n
*						Gets URI string from a record by calendar_record_get_uri_p\n
*						Destroy a calendar record handle by calendar_record_destroy
* @apicovered			calendar_record_get_uri_p, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_get_uri_p and a valid uri string pointer
* @failcase				If target APIs calendar_record_get_uri_p or uri string pointer is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_get_uri_p_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	char* pszUriStr = NULL;

	//Precondition
	if ( CreateCalendarRecord(&hRecord) == FAIL )
	{
		return 1;
	}

	// Target API
	int nRetVal = calendar_record_get_uri_p(hRecord, &pszUriStr);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_uri_p", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));
	CHECK_HANDLE_CLEANUP(pszUriStr, "calendar_record_get_uri_p", calendar_record_destroy(hRecord, true));

	// Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Makes a clone of a given record's child record list
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_clone_child_record_list_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Makes a clone of a given record's child record list
* @scenario				Create parent and child records\n
*						Insert child record in parent record\n
*						Make clone of a given record's child record list by calendar_record_clone_child_record_list\n
*						Destroy record and list
* @apicovered			calendar_record_clone_child_record_list, calendar_record_create, calendar_record_add_child_record, calendar_record_destroy, calendar_list_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_clone_child_record_list and list handle is not NULL
* @failcase				If target API calendar_record_clone_child_record_list fails or list handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_clone_child_record_list_p(void)
{
	START_TEST;

	calendar_record_h hRecord = NULL;
	calendar_record_h hAlarm = NULL;
	calendar_list_h hList = NULL;

	//Precondition
	//create records
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_create(_calendar_alarm._uri, &hAlarm);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	//add child record to parent record
	nRetVal = calendar_record_add_child_record(hRecord, _calendar_event.calendar_alarm, hAlarm);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm, true));

	// Target API
	nRetVal = calendar_record_clone_child_record_list(hRecord, _calendar_event.calendar_alarm, &hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_clone_child_record_list", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm, true));

	CHECK_HANDLE_CLEANUP(hList, "calendar_record_clone_child_record_list", calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm, true));

	//Postcondition
	//destroy record
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	//destroy list
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	return 0;
}

//& purpose:	Gets a child record handle pointer from the parent record
//& type  :		Auto
/**
* @testcase 			ITc_calendar_record_get_child_record_at_p_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a child record handle pointer from the parent record
* @scenario				Create parent and child records\n
*						Insert child records in parent record\n
*						Get child record pointer from the parent record by calendar_record_get_child_record_at_p\n
*						Destroy record and list
* @apicovered			calendar_record_get_child_record_at_p, calendar_record_create, calendar_record_add_child_record, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_record_get_child_record_at_p and child record handle is not NULL
* @failcase				If target API calendar_record_get_child_record_at_p fails or child record handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_record_get_child_record_at_p_p(void)
{
	START_TEST;
	int nIndex = 1;

	calendar_record_h hRecord = NULL;
	calendar_record_h hAlarm1 = NULL;
	calendar_record_h hAlarm2 = NULL;

	//Precondition
	//create records
	int nRetVal = calendar_record_create(_calendar_event._uri, &hRecord);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_record_create(_calendar_alarm._uri, &hAlarm1);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	nRetVal = calendar_record_create(_calendar_alarm._uri, &hAlarm2);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm1, true));

	//add child records to parent record
	nRetVal = calendar_record_add_child_record(hRecord, _calendar_event.calendar_alarm, hAlarm1);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm1, true);calendar_record_destroy(hAlarm2, true));

	nRetVal = calendar_record_add_child_record(hRecord, _calendar_event.calendar_alarm, hAlarm2);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true);calendar_record_destroy(hAlarm2, true));

	calendar_record_h hGetRec = NULL;

	// Target API
	nRetVal = calendar_record_get_child_record_at_p(hRecord, _calendar_event.calendar_alarm, nIndex, &hGetRec);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_get_child_record_at_p", CalendarServiceGetError(nRetVal), calendar_record_destroy(hRecord, true));

	CHECK_HANDLE_CLEANUP(hGetRec, "calendar_record_get_child_record_at_p", calendar_record_destroy(hRecord, true));

	//Postcondition
	nRetVal = calendar_record_destroy(hRecord, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}


/** @} */
/** @} */
