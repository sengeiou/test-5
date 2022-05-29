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
void ITs_calendar_service2_vcalendar_startup(void)
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
void ITs_calendar_service2_vcalendar_cleanup(void)
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
* @function 		CalenderServiceVcalParseToCalForEachCallback
* @description	 	callback for calendar record parse
* @parameter		record : view uri, user_data : user data
* @return 			NA
*/
static bool CalenderServiceVcalParseToCalForEachCallback(calendar_record_h record, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Vcalendar parse to calendar foreach callback\\n", __LINE__, API_NAMESPACE);
	return true;
}

/** @addtogroup itc-calendar-service2-testcases
*  @brief 		Integration testcases for module calendar-service2
*  @ingroup 	itc-calendar-service2
*  @{
*/


//& purpose:	Retrieves vcalendar stream from a calendar list
//& type  :		Auto
/**
* @testcase 			ITc_calendar_vcalendar_make_from_records_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves vcalendar stream from a calendar list
* @scenario				Create records and add them to calender list\n
*						Retrieve vcalendar stream from calendar list by calendar_vcalendar_make_from_records\n
*						Destroy list
* @apicovered			calendar_vcalendar_make_from_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_vcalendar_make_from_records and child record handle is not NULL
* @failcase				If target API calendar_vcalendar_make_from_records fails or child record handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_vcalendar_make_from_records_p(void)
{
	START_TEST;

	char *pszVcalStream = NULL;
	calendar_list_h hList = NULL;

	//Precondition
	//create calendar list with records
	if ( CreateCalendarList(&hList) == FAIL )
	{
		return 1;
	}

	// Target API
	int nRetVal = calendar_vcalendar_make_from_records(hList, &pszVcalStream);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_make_from_records", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true));

	CHECK_HANDLE_CLEANUP(pszVcalStream, "calendar_vcalendar_make_from_records", calendar_list_destroy(hList, true));

	//Postcondition
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	FREE_MEMORY(pszVcalStream);

	return 0;
}

//& purpose:	Retrieves all calendars from a vcalendar stream
//& type  :		Auto
/**
* @testcase 			ITc_calendar_vcalendar_parse_to_calendar_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all calendars from a vcalendar stream in form of calendar list
* @scenario				Create records and add them to calender list\n
*						Generate vcalendar stream from the calendar list\n
*						Retrieves all records from vcalendar stream by calendar_vcalendar_parse_to_calendar\n
*						Destroy list
* @apicovered			calendar_vcalendar_parse_to_calendar, calendar_vcalendar_make_from_records
* @passcase				CALENDAR_ERROR_NONE returned by calendar_vcalendar_parse_to_calendar and list handle is not NULL
* @failcase				If target API calendar_vcalendar_parse_to_calendar fails or list handle is NULL or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_vcalendar_parse_to_calendar_p(void)
{
	START_TEST;
	char *pszVcalStream = NULL;
	calendar_list_h hList = NULL;
	calendar_list_h hOutList = NULL;

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
	nRetVal = calendar_vcalendar_parse_to_calendar(pszVcalStream, &hOutList);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_parse_to_calendar", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true);FREE_MEMORY(pszVcalStream));

	CHECK_HANDLE_CLEANUP(hOutList, "calendar_vcalendar_parse_to_calendar", calendar_list_destroy(hList, true);FREE_MEMORY(pszVcalStream));

	//Postcondition
	//destroy lists
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_list_destroy(hOutList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));
	FREE_MEMORY(pszVcalStream);

	return 0;
}


//& purpose:	Retrieves all events or to-dos from a vCalendar file
//& type  :		Auto
/**
* @testcase 			ITc_calendar_vcalendar_parse_to_calendar_foreach_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves all events or to-dos from a vCalendar file
* @scenario				Create records and add them to calender list\n
*						Generate vcalendar stream from the calendar list\n
*						Retrieves all events or to-dos from a vCalendar file by calendar_vcalendar_parse_to_calendar_foreach\n
*						Destroy list
* @apicovered			calendar_vcalendar_parse_to_calendar_foreach, calendar_vcalendar_make_from_records, calendar_list_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_vcalendar_parse_to_calendar_foreach and callback function is hit
* @failcase				If target API calendar_vcalendar_parse_to_calendar_foreach fails or callback function is not hit or any precondition API fails.
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_vcalendar_parse_to_calendar_foreach_p(void)
{
	START_TEST;

	char *pszVcalStream = NULL;
	calendar_list_h hList = NULL;

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
	size_t nBytes = strlen(pszVcalStream);

	// write stream buffer to file
	FILE* pFptr = fopen(VCAL_FILE_PATH, "w+");
	if ( !pFptr )
	{
		FPRINTF("[Line : %d][%s] calendar_vcalendar_parse_to_calendar_foreach failed in precondition, Unable to open Vcal stream file\\n", __LINE__, API_NAMESPACE);
		calendar_list_destroy(hList, true);
		FREE_MEMORY(pszVcalStream);
		return 1;
	}
	fwrite(pszVcalStream, SIZE, nBytes, pFptr);
	fclose(pFptr);

	// Target API
	nRetVal = calendar_vcalendar_parse_to_calendar_foreach(VCAL_FILE_PATH, CalenderServiceVcalParseToCalForEachCallback, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_vcalendar_parse_to_calendar_foreach", CalendarServiceGetError(nRetVal), calendar_list_destroy(hList, true);FREE_MEMORY(pszVcalStream));

	//Postcondition
	nRetVal = calendar_list_destroy(hList, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_list_destroy", CalendarServiceGetError(nRetVal));

	FREE_MEMORY(pszVcalStream);
	return 0;
}


/** @} */
/** @} */
