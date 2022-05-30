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
void ITs_calendar_service2_query_startup(void)
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
void ITs_calendar_service2_query_cleanup(void)
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


//& purpose:	Creates and destroys a query handle
//& type  :		Auto
/**
* @testcase 			ITc_calendar_query_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a list handle
* @scenario				Creates a query handle\n
* 						Destroys the query handle
* @apicovered			calendar_query_create, calendar_query_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_query_create and calendar_query_destroy and query fetched by calendar_query_create is not NULL.
* @failcase				If target APIs calendar_query_create and calendar_query_destroy fails or query fetched by calendar_query_create is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_query_create_destroy_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 0;
	calendar_query_h query = NULL;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURI(szURI);
	int nTotalURICount = MAX_URI_COUNT;

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Target APIs
		query = NULL;
		nRetVal = calendar_query_create(szURI[nURICount], &query);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(query, "calendar_query_create");

		nRetVal = calendar_query_destroy(query);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));
	}

	return 0;
}

//& purpose:	Sets the distinct option for projection
//& type  :		Auto
/**
* @testcase 			ITc_calendar_query_set_distinct_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets the distinct option for projection
* @scenario				Creates a query handle\n
*						Set distinct option for projection by API calendar_query_set_distinct\n
* 						Destroys the query handle
* @apicovered			calendar_query_set_distinct
* @passcase				CALENDAR_ERROR_NONE returned by calendar_query_set_distinct
* @failcase				If target API calendar_query_set_distinct fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a query handle
* @postcondition		Disconnects from the calendar service and destroys the query handle
*/
int ITc_calendar_query_set_distinct_p(void)
{
	START_TEST;

	int nRetVal = -1, nURICount = 0;
	calendar_query_h query = NULL;
	char szURI[MAX_ROW][MAX_COL];
	GetViewURI(szURI);
	int nTotalURICount = MAX_URI_COUNT;

	for ( nURICount = 0; nURICount<nTotalURICount; nURICount++ )
	{
		// Preconditions
		// create query handle
		query = NULL;
		nRetVal = calendar_query_create(szURI[nURICount], &query);
		PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_create", CalendarServiceGetError(nRetVal));
		CHECK_HANDLE(query, "calendar_query_create");

		// Target APIs
		nRetVal = calendar_query_set_distinct(query, true);
		PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_set_distinct", CalendarServiceGetError(nRetVal), 	calendar_query_destroy(query));

		//Postconditions
		// destroy query handle
		nRetVal = calendar_query_destroy(query);
		PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));
	}

	return 0;
}

//& purpose:	Adds property IDs for projection
//& type  :		Auto
/**
* @testcase 			ITc_calendar_query_set_projection_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a query handle\n
*						Sets property IDs for projection by API calendar_query_set_projection\n
* 						Destroys the query handle
* @apicovered			calendar_query_set_projection
* @passcase				CALENDAR_ERROR_NONE returned by calendar_query_set_projection
* @failcase				If target API calendar_query_set_projection fails or any precondition API fails.
* @precondition			Connects to the calendar service and creates a query handle
* @postcondition		Disconnects from the calendar service and destroys the query handle
*/
int ITc_calendar_query_set_projection_p(void)
{
	START_TEST;

	calendar_query_h query = NULL;
	unsigned int nIds[2] = {_calendar_book.id, _calendar_book.name};
	int nPropCount = 2;

	// Preconditions
	// create query handle
	int nRetVal = calendar_query_create(_calendar_book._uri, &query);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(query, "calendar_query_create");

	// Target APIs
	nRetVal = calendar_query_set_projection(query, nIds, nPropCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_set_projection", CalendarServiceGetError(nRetVal), calendar_query_destroy(query));

	//Postconditions
	// destroy query handle
	nRetVal = calendar_query_destroy(query);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Sets the filter for a query and sets the sort mode
//& type  :		Auto
/**
* @testcase 			ITc_calendar_query_set_sort_filter_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Sets property IDs for projection
* @scenario				Creates a query handle\n
*						Creates a filter by calendar_filter_create\n
*						Sets the filter by calendar_query_set_filter\n
*						Sorts the query by calendar_query_set_sort\n
* 						Destroys the query handle
* @apicovered			calendar_query_set_filter, calendar_query_set_sort
* @passcase				CALENDAR_ERROR_NONE returned by calendar_query_set_filter and calendar_query_set_sort
* @failcase				If target APIs calendar_query_set_filter and calendar_query_set_sort fail or any precondition API fails.
* @precondition			Connects to the calendar service and creates a query handle, creates a filter and sets the filter
* @postcondition		Disconnects from the calendar service and destroys the query handle
*/
int ITc_calendar_query_set_sort_filter_p(void)
{
	START_TEST;

	calendar_query_h query = NULL;
	calendar_filter_h filter = NULL;

	// Preconditions
	// create query handle
	int nRetVal = calendar_query_create(_calendar_event._uri, &query);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_create", CalendarServiceGetError(nRetVal));
	CHECK_HANDLE(query, "calendar_query_create");

	// create filter
	nRetVal = calendar_filter_create(_calendar_event._uri, &filter);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_create", CalendarServiceGetError(nRetVal), calendar_query_destroy(query));
	CHECK_HANDLE_CLEANUP(filter, "calendar_filter_create", calendar_query_destroy(query));

	// add condition for int property
	nRetVal = calendar_filter_add_str(filter, _calendar_event.summary, CALENDAR_MATCH_FULLSTRING, "API TESTING");
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_add_str", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter);calendar_query_destroy(query));


	// Target APIs
	nRetVal = calendar_query_set_filter(query, filter);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_set_filter", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter);calendar_query_destroy(query));

	nRetVal = calendar_query_set_sort(query, _calendar_event.start_time, true);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_set_sort", CalendarServiceGetError(nRetVal), calendar_filter_destroy(filter);calendar_query_destroy(query));

	//Postconditions
	// destroy filter
	nRetVal = calendar_filter_destroy(filter);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_filter_destroy", CalendarServiceGetError(nRetVal));

	// destroy query handle
	nRetVal = calendar_query_destroy(query);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_query_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}


/** @} */
/** @} */
