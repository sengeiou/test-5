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
void ITs_calendar_service2_reminder_startup(void)
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
void ITs_calendar_service2_reminder_cleanup(void)
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
* @function 		CalenderServiceReminderAlarmCallback
* @description	 	callback for calendar alarm
* @parameter		param : parameter, user_data : user data
* @return 			NA
*/
static void CalenderServiceReminderAlarmCallback(const char *param, void *user_data)
{
	FPRINTF("[Line : %d][%s] Inside Reminder Alarm callback\\n", __LINE__, API_NAMESPACE);
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

//& purpose:	Registers a callback function to be invoked when a reminder alarm is alerted and unregisters the callback function
//& type  :		Auto
/**
* @testcase 			ITc_calendar_reminder_add_remove_cb_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Registers a callback function to be invoked when a reminder alarm is alerted and unregisters the callback function
* @scenario				Create and inserts a record to the calendar database\n
*						Registers a callback function to be invoked when a reminder alerts by calendar_reminder_add_cb\n
*						Updates a record in the calendar database\n
*						Unregisters the callback function by calendar_reminder_remove_cb\n
*						Delete the record from the calendar database by calendar_db_delete_record\n
*						Delete the record by calendar_record_destroy
* @apicovered			calendar_reminder_add_cb, calendar_reminder_remove_cb, calendar_db_insert_record, calendar_record_create, calendar_record_destroy
* @passcase				CALENDAR_ERROR_NONE returned by calendar_reminder_add_cb and calendar_reminder_remove_cb and required callback function is hit
* @failcase				If target API calendar_reminder_add_cb and calendar_reminder_remove_cb fails or required callback function is not hit or any precondition API fails
* @precondition			Connects to the calendar service
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_reminder_add_remove_cb_p(void)
{
	START_TEST;

	calendar_time_s stAlarmTime = {0};
	g_nCheckCb = false;
	int nEventId = -1;
	calendar_record_h hParent = NULL;
	calendar_record_h hAlarm = NULL;
	int nTtimeoutId = 0;
	g_pMainLoop = g_main_loop_new(NULL, false);

	//Precondition
	// create parent record
	int nRetVal = calendar_record_create(_calendar_event._uri, &hParent);
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal));


	// create alarm child records
	nRetVal = calendar_record_create(_calendar_alarm._uri, &hAlarm);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_create", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true));

	nRetVal = calendar_record_set_int(hAlarm, _calendar_alarm.tick_unit, CALENDAR_ALARM_TIME_UNIT_SPECIFIC);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_int", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true);calendar_record_destroy(hAlarm, true));

	time_t current_time = time(NULL) + 4;
	FPRINTF("[Line : %d][%s] alarm time set = %ld\\n", __LINE__, API_NAMESPACE, current_time);

	stAlarmTime.time.utime = (long long int)current_time;
	nRetVal = calendar_record_set_caltime(hAlarm, _calendar_alarm.alarm_time, stAlarmTime);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_set_caltime", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true);calendar_record_destroy(hAlarm, true));

	nRetVal = calendar_record_add_child_record(hParent, _calendar_event.calendar_alarm, hAlarm);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_add_child_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true);calendar_record_destroy(hAlarm, true));

	// insert record
	nRetVal = calendar_db_insert_record(hParent, &nEventId);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_db_insert_record", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true));

	// Target APIs
	nRetVal = calendar_reminder_add_cb(CalenderServiceReminderAlarmCallback, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_reminder_add_cb", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true));

	current_time = time(NULL);
	FPRINTF("[Line : %d][%s] current time inside loop before wait calendar_reminder_add_cb = %ld\\n", __LINE__, API_NAMESPACE, current_time);

	nTtimeoutId = g_timeout_add(10000, Timeout_Function, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTtimeoutId);

	current_time = time(NULL);
	FPRINTF("[Line : %d][%s] current time inside loop after wait calendar_reminder_add_cb = %ld\\n", __LINE__, API_NAMESPACE, current_time);

	if ( g_nCheckCb == false )
	{
		FPRINTF("[Line : %d][%s] calendar_reminder_add_cb failed as callback is not hit\\n", __LINE__, API_NAMESPACE);
		calendar_record_destroy(hParent, true);
		return 1;
	}

	nRetVal = calendar_reminder_remove_cb(CalenderServiceReminderAlarmCallback, NULL);
	PRINT_RESULT_CLEANUP(CALENDAR_ERROR_NONE, nRetVal, "calendar_reminder_add_cb", CalendarServiceGetError(nRetVal), calendar_record_destroy(hParent, true));

	//Postconditions
	nRetVal = calendar_record_destroy(hParent, true);
	PRINT_RESULT_NORETURN(CALENDAR_ERROR_NONE, nRetVal, "calendar_record_destroy", CalendarServiceGetError(nRetVal));

	return 0;
}

/** @} */
/** @} */
