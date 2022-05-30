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
void ITs_calendar_service2_list_startup(void)
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
void ITs_calendar_service2_list_cleanup(void)
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

//& purpose:	Creates and destroys calendar list handle.
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_create_destroy_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a list handle
* @scenario				Creates a list handle\n
* 						Destroys a list handle
* @apicovered			calendar_list_create,  calendar_list_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_create and calendar_list_destroy.
* @failcase				If target APIs calendar_list_create or calendar_list_destroy fails or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_list_create_destroy_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;

	// Target APIs
	int nRetVal = calendar_list_create(&hList);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_create", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Adds and remove a record in the calendar list
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_add_remove_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Adds and remove a record in the calendar list
* @scenario				Add a record in the calender list\n
* 						Removes a record from the calender list
* @apicovered			calendar_list_add,  calendar_list_remove
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_add and calendar_list_remove.
* @failcase				If target APIs calendar_list_add or calendar_list_remove fails or any precondition API fails.
* @precondition			Connects to the calendar service, create a calender list and create an event
* @postcondition		Disconnects from the calendar service, destroy the calender list and the event
*/
int ITc_calendar_list_add_remove_p(void)
{
	START_TEST;

	calendar_record_h event = NULL;
	calendar_list_h hList = NULL;

	// Preconditions
	// create an event
	if ( CreateCalendarRecord(&event) == FAIL )
	{
		return 1;
	}

	// create list
	int nRetVal = calendar_list_create(&hList);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_create", CalendarServiceGetError(nRetVal));

	// Target APIs
	nRetVal = calendar_list_add(hList, event);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_add", CalendarServiceGetError(nRetVal), calendar_record_destroy(event,true);calendar_list_destroy(hList, true) );

	nRetVal = calendar_list_remove(hList, event);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_remove", CalendarServiceGetError(nRetVal), calendar_record_destroy(event,true);calendar_list_destroy(hList, true) );

	// Postconditions
	// destroy record
	nRetVal = calendar_record_destroy(event,true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal))

		// destroy list
		nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal))

		return 0;
}

//& purpose:	Moves a calendar list to the first position and last position
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_first_last_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a calendar list to the first and last positions
* @scenario				Moves a calendar list to the first position\n
* 						Moves a calendar list to the last position
* @apicovered			calendar_list_first, calendar_list_last
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_first and calendar_list_last
* @failcase				If target APIs calendar_list_first and calendar_list_last fail or any precondition API fails.
* @precondition			Connects to the calendar service, create a calender list and create events, add events in the calender list
* @postcondition		Disconnects from the calendar service, destroy the calender list and the events, removes events from the calender list
*/
int ITc_calendar_list_first_last_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;

	// Preconditions
	//create calendar list with records
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// Target APIs
	int nRetVal = calendar_list_first(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_first", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true) );

	nRetVal = calendar_list_last(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_last", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true) );

	// Postconditions
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Fetch the number of entities in a calendar list
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_get_count_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Fetch the number of entities in a calendar list
* @scenario				create a calender list and create events, add events in the calender list\n
*						fetch number of entries in the calendar list\n
* 						destroy the calender list and the events, removes events from the calender list
* @apicovered			calendar_list_get_count
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_get_count and recieves the number of entries in the calendar list
* @failcase				If target API calendar_list_get_count fails or doesn't fetch the number of entries or any precondition API fails
* @precondition			Connects to the calendar service, create a calender list and create events, add events in the calender list
* @postcondition		Disconnects from the calendar service, destroy the calender list and the events, removes events from the calender list
*/
int ITc_calendar_list_get_count_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;
	int nCount = 0;

	// Preconditions
	//create calendar list with three records
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// Target API
	int nRetVal = calendar_list_get_count(hList,&nCount);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_get_count", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));
	PRINT_RESULT_CLEANUP(3, nCount, "calendar_list_get_count", "Output parameter doesn't match the set value", calendar_list_destroy(hList, true)); // Three records created in CreateCalendarList

	// Postconditions
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Retrieves a record from a calendar list
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_get_current_record_p_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Fetch the number of entities in a calendar list\n
* @scenario				create a calender list and create events, add events in the calender list\n
*						fetch a record from the calendar list\n
* 						destroy the calender list and the events, removes events from the calender list
* @apicovered			calendar_list_get_current_record_p
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_get_current_record_p and fetched record is not null
* @failcase				If target API calendar_list_get_current_record_p fails or fetched record is not null or any precondition API fails
* @precondition			Connects to the calendar service, create a calender list and create events, add events in the calender list
* @postcondition		Disconnects from the calendar service, destroy the calender list and the events, removes events from the calender list
*/
int ITc_calendar_list_get_current_record_p_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;
	calendar_record_h currRecord = NULL;

	// Preconditions
	//create calendar list
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// calendar list to the first position
	int nRetVal = calendar_list_first(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_first", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	// Target API
	nRetVal = calendar_list_get_current_record_p(hList,&currRecord);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_get_current_record_p", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));
	CHECK_HANDLE_CLEANUP(currRecord, "calendar_list_get_current_record_p", calendar_list_destroy(hList, true));

	// Postcondition
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

//& purpose:	Moves calendar list to the next position and previous position
//& type  :		Auto
/**
* @testcase 			ITc_calendar_list_next_prev_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a calendar list to the next and previous positions
* @scenario				Moves a calendar list to the next position\n
* 						Moves a calendar list to the previous position
* @apicovered			calendar_list_next, calendar_list_prev
* @passcase				CALENDAR_ERROR_NONE returned by calendar_list_next and calendar_list_prev
* @failcase				If target APIs calendar_list_next and calendar_list_prev fail or any precondition API fails.
* @precondition			Connects to the calendar service, create a calender list and create events, add events in the calender list
* @postcondition		Disconnects from the calendar service, destroy the calender list and the events, removes events from the calender list
*/
int ITc_calendar_list_next_prev_p(void)
{
	START_TEST;

	calendar_list_h hList = NULL;

	// Preconditions
	//create calendar list
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// calendar list to the first position
	int nRetVal = calendar_list_first(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_first", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	// Target APIs
	nRetVal = calendar_list_next(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_next", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	nRetVal = calendar_list_prev(hList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_prev", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	// Postconditions
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */
