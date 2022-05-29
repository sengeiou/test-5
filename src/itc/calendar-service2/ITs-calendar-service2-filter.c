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

calendar_match_str_flag_e nCalendarStrMatchFlag[] = {CALENDAR_MATCH_EXACTLY, CALENDAR_MATCH_FULLSTRING, CALENDAR_MATCH_CONTAINS,
CALENDAR_MATCH_STARTSWITH, CALENDAR_MATCH_ENDSWITH, CALENDAR_MATCH_EXISTS};

calendar_match_int_flag_e nCalendarIntMatchFlag[] = {CALENDAR_MATCH_EQUAL, CALENDAR_MATCH_GREATER_THAN, CALENDAR_MATCH_GREATER_THAN_OR_EQUAL,
CALENDAR_MATCH_LESS_THAN, CALENDAR_MATCH_LESS_THAN_OR_EQUAL, CALENDAR_MATCH_NOT_EQUAL,
CALENDAR_MATCH_NONE};

calendar_filter_operator_e nCalendarFilterOperator[] = {CALENDAR_FILTER_OPERATOR_AND, CALENDAR_FILTER_OPERATOR_OR};


/**
* @function 		ITs_calendar_service_startup
* @description	 	Called before each test, connects to the calendar service
* @parameter		NA
* @return 			NA
*/
void ITs_calendar_service2_filter_startup(void)
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
void ITs_calendar_service2_filter_cleanup(void)
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

//& purpose:	Creates and destroys calendar filter handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a calendar filter handle and destroys the filter handle
* @scenario				Creates a filter handle\n
* 						Destroys the filter handle
* @apicovered			calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_create and calendar_filter_destroy and filter handle created is not NULL.
* @failcase				If target APIs calendar_filter_create or calendar_filter_destroy, or filter handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_filter_create_destroy_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 0;
	calendar_filter_h  filter = NULL;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURI(szURI);
	int nTotalURICount = MAX_URI_COUNT;

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target APIs
		nRetVal = calendar_filter_create(szURI[nURICount], &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}

	return 0;
}

//& purpose:	Adds a condition in the calendar filter for a calendar_time_s property
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_caltime_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection\n
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_caltime\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_caltime, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_caltime
* @failcase				If target API calendar_filter_add_caltime fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_caltime_p(void)
{
	START_TEST;

	int nRetVal = -1, nIntFlagCount = 0;
	calendar_filter_h filter = NULL;
	calendar_time_s stCalTime = {0};

	stCalTime.type = CALENDAR_TIME_UTIME;
	stCalTime.time.date.year = 2014;
	stCalTime.time.date.month = 06;
	stCalTime.time.date.mday = 23;
	int nIntTotalFlagCount = sizeof(nCalendarIntMatchFlag)/sizeof(nCalendarIntMatchFlag[0]);

	for ( nIntFlagCount = 0; nIntFlagCount< nIntTotalFlagCount; nIntFlagCount++ )
	{
		// Precondition
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		// Target API
		nRetVal = calendar_filter_add_caltime(filter, _calendar_event.start_time, nCalendarIntMatchFlag[nIntFlagCount], stCalTime);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_caltime", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds a condition in the calendar filter for double type property
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_double_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_double\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_double, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_double
* @failcase				If target API calendar_filter_add_double fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_double_p(void)
{
	START_TEST;

	int nRetVal = -1, nIntFlagCount = 0;
	calendar_filter_h filter = NULL;
	double nMatchValue = 1.0;
	int nIntTotalFlagCount = sizeof(nCalendarIntMatchFlag)/sizeof(nCalendarIntMatchFlag[0]);

	for ( nIntFlagCount = 0; nIntFlagCount< nIntTotalFlagCount; nIntFlagCount++ )
	{
		// Precondition
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		// Target API
		nRetVal = calendar_filter_add_double(filter, _calendar_event.latitude, nCalendarIntMatchFlag[nIntFlagCount], nMatchValue);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_caltime", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds a condition in the calendar filter for integer type property
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_int_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_int\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_int, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_int
* @failcase				If target API calendar_filter_add_int fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_int_p(void)
{
	START_TEST;

	int nRetVal = -1, nIntFlagCount = 0;
	calendar_filter_h filter = NULL;
	int nMatchValue = 1;
	int nIntTotalFlagCount = sizeof(nCalendarIntMatchFlag)/sizeof(nCalendarIntMatchFlag[0]);

	for ( nIntFlagCount = 0; nIntFlagCount< nIntTotalFlagCount; nIntFlagCount++ )
	{
		// Precondition
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		// Target API
		nRetVal = calendar_filter_add_int(filter, _calendar_event.id, nCalendarIntMatchFlag[nIntFlagCount], nMatchValue);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_int", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds a condition in the calendar filter for long long integer type property
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_lli_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_lli\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_lli, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_lli
* @failcase				If target API calendar_filter_add_lli fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_lli_p(void)
{
	START_TEST;

	int nRetVal = -1, nIntFlagCount = 0;
	calendar_filter_h filter = NULL;
	long long int nLongInt = (60 * 80 * 24 * 50 * 60);
	int nIntTotalFlagCount = sizeof(nCalendarIntMatchFlag)/sizeof(nCalendarIntMatchFlag[0]);

	for ( nIntFlagCount = 0; nIntFlagCount< nIntTotalFlagCount; nIntFlagCount++ )
	{
		// Precondition
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		// Target API
		nRetVal = calendar_filter_add_lli(filter, _calendar_event.created_time, nCalendarIntMatchFlag[nIntFlagCount], nLongInt);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_lli", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds a condition in the calendar filter for string type property
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_str_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_str\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_str, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_str
* @failcase				If target API calendar_filter_add_str fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_str_p(void)
{
	START_TEST;

	int nRetVal = -1, nStrFlagCount = 0;
	calendar_filter_h filter = NULL;
	const char *pszString = "Tizen Test";
	int nStrTotalFlagCount = sizeof(nCalendarStrMatchFlag)/sizeof(nCalendarStrMatchFlag[0]);

	for ( nStrFlagCount = 0; nStrFlagCount< nStrTotalFlagCount; nStrFlagCount++ )
	{
		// Precondition
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		// Target API
		nRetVal = calendar_filter_add_str(filter, _calendar_event.summary, nCalendarStrMatchFlag[nStrFlagCount], pszString);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_lli", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds an operator between conditions of calendar filter
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_operator_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_filter_add_operator\n
*						Destroys the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_operator, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_operator
* @failcase				If target API calendar_filter_add_operator fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a filter handle
* @postcondition		Disconnects from the calendar service and destroys the filter handle
*/
int ITc_calendar_filter_add_operator_p(void)
{
	START_TEST;

	int nRetVal = -1, nFilterFlagCount = 0;
	calendar_filter_h filter = NULL;
	calendar_time_s stCalTime = {0};

	stCalTime.type = CALENDAR_TIME_UTIME;
	stCalTime.time.date.year = 2014;
	stCalTime.time.date.month = 06;
	stCalTime.time.date.mday = 23;
	int nFilterTotalFlagCount = sizeof(nCalendarFilterOperator)/sizeof(nCalendarFilterOperator[0]);

	for ( nFilterFlagCount = 0; nFilterFlagCount< nFilterTotalFlagCount; nFilterFlagCount++ )
	{
		// Preconditions
		nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(filter, "calendar_filter_create");

		nRetVal = calendar_filter_add_caltime(filter, _calendar_event.start_time, CALENDAR_MATCH_GREATER_THAN, stCalTime);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_caltime", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));
		// Target API
		nRetVal = calendar_filter_add_operator(filter, nCalendarFilterOperator[nFilterFlagCount]);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_operator", CalendarServiceGetError(nRetVal), 	calendar_filter_destroy(filter));

		//Postcondition
		nRetVal = calendar_filter_destroy(filter);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));
	}
	return 0;
}

//& purpose:	Adds a child filter to a filter
//& type  :		Auto
/**
* @testcase 			ITc_calendar_filter_add_filter_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a parent filter by calendar_filter_create\n
*						Creates a child filter by calendar_filter_create\n
*						Adds child filter to parent filter by calendar_filter_add_filter\n
*						Destroys both the filter handle by calendar_filter_destroy
* @apicovered			calendar_filter_add_filter, calendar_filter_create, calendar_filter_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_filter_add_filter
* @failcase				If target API calendar_filter_add_filter fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates filter handles
* @postcondition		Disconnects from the calendar service and destroy filter handles
*/
int ITc_calendar_filter_add_filter_p(void)
{
	START_TEST;

	calendar_filter_h filter1 = NULL;
	calendar_filter_h filter2 = NULL;
	calendar_time_s stStartTime = {0};
	calendar_time_s stEndTime = {0};

	stStartTime.type = CALENDAR_TIME_UTIME;
	stStartTime.time.date.year = 2014;
	stStartTime.time.date.month = 06;
	stStartTime.time.date.mday = 23;

	stEndTime.type = CALENDAR_TIME_UTIME;
	stEndTime.time.date.year = 2014;
	stEndTime.time.date.month = 07;
	stEndTime.time.date.mday = 20;

	// Preconditions
	// create filter 1
	int nRetVal = calendar_filter_create(_calendar_event._uri, &filter1);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(filter1, "calendar_filter_create");

	nRetVal = calendar_filter_add_caltime(filter1, _calendar_event.start_time, CALENDAR_MATCH_GREATER_THAN, stStartTime);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_caltime", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter1));

	nRetVal = calendar_filter_add_operator(filter1, CALENDAR_FILTER_OPERATOR_AND);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_operator", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter1));

	// create filter 2
	nRetVal = calendar_filter_create(_calendar_event._uri, &filter2);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(filter2, "calendar_filter_create");

	nRetVal = calendar_filter_add_caltime(filter2, _calendar_event.end_time, CALENDAR_MATCH_LESS_THAN_OR_EQUAL, stEndTime);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_caltime", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter2));

	//Target API
	nRetVal = calendar_filter_add_filter(filter1,filter2);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_operator", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter1);calendar_filter_destroy(filter2));
	//Postconditions
	nRetVal = calendar_filter_destroy(filter1);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_filter_destroy(filter2);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */
