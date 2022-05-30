//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	 http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-alarm-common.h"

/** @addtogroup itc-alarm
*  @ingroup itc
*  @{
*/
//& set: Application

int g_AlarmRegisteredReceived = 0;
int g_AlarmIDValueReceived = -1;

bool g_bCallBackHit_alarm = false;
bool g_bUserDataMismatch_alarm = false;

void *g_pUserData_alarm = "user_data_1";


/**
* @function 		ITs_alarm_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_alarm_startup(void)
{
	g_bCallBackHit_alarm = false;
	g_bUserDataMismatch_alarm = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_alarm_startup\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_HELLOWORLD_APPID, TEST_TESTAPPLICATION_APPID);
	return;
}

/**
* @function 		ITs_alarm_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_alarm_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_alarm_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		registered_alarm_cb
* @description	 	callback function for registered alarm
* @parameter		nAlarmID : alarm ID, user_data : user data sent to callback
* @return 			true
*/
bool registered_alarm_cb(int nAlarmID, void *user_data)
{
	g_bCallBackHit_alarm = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_alarm) != 0)
	{
		g_bUserDataMismatch_alarm = true;
	}

	FPRINTF("[Line : %d][%s] registered_alarm_cb invoked;alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);

	g_AlarmIDValueReceived = nAlarmID;
	++g_AlarmRegisteredReceived;
	return true;
}

//& type: auto
//& purpose: Set Alarm after Delay.
/**
* @testcase 			ITc_alarm_schedule_once_after_delay_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set Alarm after delay and checks the Alarm ID.
* @scenario				Create AppControl\n
*						Set Alarm after Delay\n
*						Check Alarm ID\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, alarm_schedule_once_after_delay, alarm_cancel, app_control_set_operation, app_control_set_app_id
* @passcase				When alarm_schedule_once_after_delay is success full and return proper Alarm ID.
* @failcase				If target API fails or return value is not proper.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_once_after_delay_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min

	//Target API
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay on invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set Alarm at Date.
/**
* @testcase 			ITc_alarm_schedule_once_at_date_p
* @since_tizen			2.4
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set Alarm at date and checks the Alarm ID.
* @scenario				Create AppControl\n
*						Set Alarm at date\n
*						Check Alarm ID\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, alarm_schedule_once_at_date, alarm_cancel, app_control_set_operation, app_control_set_app_id
* @passcase				When alarm_schedule_once_at_date is successful and return proper Alarm ID.
* @failcase				If target API fails or return value is not proper.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_once_at_date_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec += 60;//set after 1 min
	int nAlarmID = -1;

	//Target API
	nRet = alarm_schedule_once_at_date(hAppControl, &stDate, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_at_date", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_at_date returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	FPRINTF("[Line : %d][%s] alarm_schedule_once_at_date returned alarm ID = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set Alarm at Date with recurrence week set option.
/**
* @testcase 			ITc_alarm_schedule_with_recurrence_week_flag_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set Alarm at date and with recurrence week flag set option.
* @scenario				Create AppControl\n
*						Set Alarm at date with recurrence week flag set option\n
*						Check Alarm ID\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, alarm_schedule_with_recurrence_week_flag, alarm_cancel, app_control_set_operation, app_control_set_app_id
* @passcase				When alarm_schedule_with_recurrence_week_flag is successful and return proper Alarm ID.
* @failcase				If target API fails or return value is not proper.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_with_recurrence_week_flag_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec += 60;//set after 1 min

	alarm_week_flag_e flag_type[] = { ALARM_WEEK_FLAG_SUNDAY,
		ALARM_WEEK_FLAG_MONDAY,
		ALARM_WEEK_FLAG_TUESDAY,
		ALARM_WEEK_FLAG_WEDNESDAY,
		ALARM_WEEK_FLAG_THURSDAY,
		ALARM_WEEK_FLAG_FRIDAY,
		ALARM_WEEK_FLAG_SATURDAY};

	int enum_size = sizeof(flag_type) / sizeof(flag_type[0]);
	int enum_counter = 0;

	for ( enum_counter=0;enum_counter<enum_size;enum_counter++ )
	{
		int nAlarmID = -1;
		int nWeekday = flag_type[enum_counter];
		//Target API
		nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, nWeekday, &nAlarmID);
		PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet), app_control_destroy(hAppControl));

		if ( nAlarmID < 0 )
		{
			FPRINTF("[Line : %d][%s] alarm_schedule_with_recurrence_week_flag for alarm_week_flag_e enum value = %d, returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, flag_type[enum_counter], nAlarmID);
			app_control_destroy(hAppControl);
			return 1;
		}

		FPRINTF("[Line : %d][%s] alarm_schedule_with_recurrence_week_flag returned alarm ID = %d for alarm_week_flag_e enum value = %d\\n", __LINE__, API_NAMESPACE, nAlarmID, flag_type[enum_counter]);
		alarm_cancel(nAlarmID);

	}

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call alarm_foreach_registered_alarm to retrieve all the registered alarms.
/**
* @testcase 			ITc_alarm_foreach_registered_alarm_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call alarm_foreach_registered_alarm to retrieve all the supported alarm information.
* @scenario				registered the alarm\n
*						call alarm_foreach_registered_alarm\n
*						check the callback and retrieve all the information
* @apicovered			alarm_foreach_registered_alarm, alarm_schedule_once_after_delay, alarm_cancel, app_control_create, app_control_set_operation, app_control_set_app_id, app_control_destroy
* @passcase				When alarm_foreach_registered_alarm is successful and callback returns proper value
* @failcase				If target API fails or callback doesn't retrieve supported alarm values.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_foreach_registered_alarm_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay failed, alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned alarm ID = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);

	g_AlarmRegisteredReceived = 0;
	g_AlarmIDValueReceived = -1;

	//Target API
	nRet = alarm_foreach_registered_alarm(registered_alarm_cb, g_pUserData_alarm);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_foreach_registered_alarm", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	if ( g_AlarmRegisteredReceived <= 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_foreach_registered_alarm returned invalid total registered alarms = %d\\n", __LINE__, API_NAMESPACE, g_AlarmRegisteredReceived);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	if(false == g_bCallBackHit_alarm)
	{
		FPRINTF("[Line : %d][%s] Callback not invoked\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}
	
	if(g_bUserDataMismatch_alarm)
	{
		FPRINTF("[Line : %d][%s] User data in callback is not same which is passed through caller function.\\n", __LINE__, API_NAMESPACE);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call alarm_get_app_control to get the app_control of the registered alarm.
/**
* @testcase 			ITc_alarm_get_app_control_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call alarm_get_app_control to get app_control of the registered alarm.
* @scenario				registered the alarm\n
*						call alarm_get_app_control\n
*						check the app_control value and compare with original
* @apicovered			alarm_get_app_control, alarm_schedule_once_after_delay, alarm_cancel, app_control_set_app_id, app_control_destroy, app_control_create, app_control_set_operation, app_control_get_app_id
* @passcase				When alarm_get_app_control is successful and returns correct value
* @failcase				If target API fails or callback doesn't retrieve correct values.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_app_control_p(void)
{
	START_TEST;

	app_control_h hAppControl;

	char* pszPackage = TEST_TESTAPPLICATION_APPID;//sample app string
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay failed, alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned alarm ID = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
	app_control_h hAppControlReceived;
	char* pszGetVal = NULL;
	//Target API
	nRet = alarm_get_app_control(nAlarmID, &hAppControlReceived);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_app_control", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));
	if ( NULL == hAppControlReceived)
	{
		FPRINTF("[Line : %d][%s] alarm_get_app_control returned NULL Handle\\n", __LINE__, API_NAMESPACE);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = app_control_get_app_id(hAppControlReceived, &pszGetVal);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "app_control_get_app_id", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	if ( NULL == pszGetVal)
	{
		FPRINTF("[Line : %d][%s] app_control_get_app_id failed, error returned = Get value is NULL\\n", __LINE__, API_NAMESPACE);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	FREE_MEMORY(pszGetVal);
	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call alarm_get_scheduled_period to get the scheduled period of the registered alarms.
/**
* @testcase 			ITc_alarm_get_scheduled_period_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call alarm_get_scheduled_period to get the scheduled period of the registered alarms.
* @scenario				registered the alarm\n
*						call alarm_get_scheduled_period\n
*						check the value received
* @apicovered			alarm_get_scheduled_period, alarm_schedule_once_after_delay, alarm_cancel, app_control_destroy, app_control_create, app_control_set_operation, app_control_set_app_id
* @passcase				When alarm_get_scheduled_period is successful and returns proper value
* @failcase				If target API fails or doesn't return correct value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_scheduled_period_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_after_delay(hAppControl, nDelay,nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	int nGetPeriod = 0;
	//Target API
	nRet = alarm_get_scheduled_period(nAlarmID, &nGetPeriod);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_scheduled_period", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	if ( nGetPeriod <= 0 )
	{
	FPRINTF("[Line : %d][%s] alarm_get_scheduled_period value returned invalid value = %d\\n", __LINE__, API_NAMESPACE, nGetPeriod);
	alarm_cancel(nAlarmID);
	app_control_destroy(hAppControl);
	return 1;
	}

	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call alarm_get_scheduled_date to get the scheduled date of the registered alarms.
/**
* @testcase 			ITc_alarm_get_scheduled_date_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call alarm_get_scheduled_date to get the scheduled date of the registered alarms.
* @scenario				registered the alarm\n
*						call alarm_get_scheduled_date\n
*						check the value received
* @apicovered			app_control_create, app_control_destroy, app_control_set_operation, app_control_set_app_id, alarm_get_scheduled_date, alarm_schedule_with_recurrence_week_flag, alarm_cancel
* @passcase				When alarm_get_scheduled_date is successful and returns proper value
* @failcase				If target API fails or doesn't return correct value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_scheduled_date_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec = 30;//set sec value to 30 sec
	int nWeekday = ALARM_WEEK_FLAG_SUNDAY;
	nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, nWeekday, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_with_recurrence_week_flag returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	struct tm stGetDate;

	//Target API
	nRet = alarm_get_scheduled_date(nAlarmID, &stGetDate);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_scheduled_date", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	if ( stGetDate.tm_min != stDate.tm_min )
	{
		FPRINTF("[Line : %d][%s] alarm_get_scheduled_date value mismatch, set second value = %d, received second value = %d\\n", __LINE__, API_NAMESPACE, stDate.tm_sec, stGetDate.tm_sec);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Call alarm_get_scheduled_recurrence_week_flag to get the scheduled recurrence_week_flag of the registered alarms.
/**
* @testcase 			ITc_alarm_get_scheduled_recurrence_week_flag_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Call alarm_get_scheduled_recurrence_week_flag to get the scheduled recurrence_week_flag of the registered alarms.
* @scenario				registered the alarm\n
*						call alarm_get_scheduled_recurrence_week_flag\n
*						check the value received
* @apicovered			app_control_create, app_control_set_operation, app_control_set_app_id, alarm_get_scheduled_recurrence_week_flag, alarm_schedule_with_recurrence_week_flag, alarm_cancel, app_control_destroy
* @passcase				When alarm_get_scheduled_recurrence_week_flag is successful and returns proper value
* @failcase				If target API fails or doesn't return correct value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_scheduled_recurrence_week_flag_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "app_control_set_operation", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec = 30;//set sec value to 30 sec
	int nWeekday = ALARM_WEEK_FLAG_SUNDAY;

	nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, nWeekday, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_with_recurrence_week_flag returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	int nGetWeekday;

	//Target API
	nRet = alarm_get_scheduled_recurrence_week_flag(nAlarmID, &nGetWeekday);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_scheduled_recurrence_week_flag", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	if ( nWeekday != nGetWeekday )
	{
		FPRINTF("[Line : %d][%s] alarm_get_scheduled_recurrence_week_flag value mismatch, set value = %d, received value = %d\\n", __LINE__, API_NAMESPACE, nWeekday, nGetWeekday);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set Alarm after Delay and cancel the alarm.
/**
* @testcase 			ITc_alarm_cancel_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set Alarm after delay and cancel the alarm.
* @scenario				Create AppControl\n
*						Set Alarm after Delay\n
*						cancel Alarm ID\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, alarm_schedule_once_after_delay, alarm_cancel, app_control_set_operation, app_control_set_app_id
* @passcase				When alarm_cancel is successful and behave properly.
* @failcase				If target API fails or not behaved properly.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_cancel_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		return 1;
	}

	//Target API
	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Set few Alarms after Delay and cancel_all the alarm.
/**
* @testcase 			ITc_alarm_cancel_all_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Set few Alarms after delay and cancel all the alarms.
* @scenario				Create AppControl\n
*						Set Alarm after Delay\n
*						Cancel all alarms\n
*						Destroy AppControl
* @apicovered			app_control_create, app_control_destroy, alarm_schedule_once_after_delay, alarm_cancel_all, app_control_set_operation, app_control_set_app_id,
* @passcase				When alarm_cancel_all is successful and behave properly.
* @failcase				If target API fails or not behaved properly.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_cancel_all_p(void)
{
	START_TEST;

	app_control_h hAppControl;
	char* pszPackage = TEST_TESTAPPLICATION_APPID;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID1 = -1;
	int nAlarmID2 = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID1);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID1 < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay failed with alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID1);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay + 60, &nAlarmID2);//set after 60 sec from first alarm
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));
	if ( nAlarmID2 < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay failed with alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID2);
		app_control_destroy(hAppControl);
		alarm_cancel_all();
		return 1;
	}

	//Target API
	nRet = alarm_cancel_all();
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "alarm_cancel_all", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Get current time.
/**
* @testcase 			ITc_alarm_get_current_time_p
* @since_tizen			2.3
* @author				SRID(satyajit.a)
* @reviewer			 	SRID(gupta.sanjay)
* @type 				auto
* @description			Get current time
* @scenario				Get current time\n
*				validate the time
* @apicovered			alarm_get_current_time
* @passcase			When alarm_get_current_time is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_current_time_p(void)
{
	START_TEST;

	struct tm stdate;

	//Target API
	int nRet = alarm_get_current_time(&stdate);
	PRINT_RESULT(ALARM_ERROR_NONE, nRet, "alarm_get_current_time", AlarmGetError(nRet));
	
	if(stdate.tm_sec < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_get_current_time returned invalid time\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

//& type: auto
//& purpose:Sets and Gets global flag in the alarm. 
/**
* @testcase 			ITc_alarm_set_get_global_p
* @since_tizen		3.0
* @author				SRID(nibha.sharma)
* @reviewer			 SRID(a.pandia1)
* @type 					auto
* @description		Get current time
* @scenario			Get current time\n
* @apicovered			alarm_get_current_time
* @passcase				When alarm_get_current_time is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_set_get_global_p(void)
{
	START_TEST;

	bool bSetGlobal = true;
	bool bGetGlobal ;
	app_control_h hAppControl;
	char *pszPackage = "org.tizen.globalapp";

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID; 
	int nDelay = 1;
	nRet = alarm_schedule_after_delay(hAppControl, nDelay,nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_set_global(nAlarmID, bSetGlobal); 
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_set_global", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));
	 
	nRet = alarm_get_global(nAlarmID, &bGetGlobal); 
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_global", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));
	 
	if(bSetGlobal != bGetGlobal)
	{
		FPRINTF("[Line : %d][%s] value mismatch\\n", __LINE__, API_NAMESPACE);
		alarm_cancel(nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}
	 
	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
 
	return 0;
}

//& type: auto
//& purpose: Sets a notification alarm to be triggered at a specific time.
/**
* @testcase 			ITc_alarm_schedule_noti_once_at_date_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets a notification alarm to be triggered at a specific time
* @scenario				Sets a notification alarm to be triggered at a specific time
* @apicovered			notification_create, notification_set_text, alarm_schedule_noti_once_at_date, notification_free
* @passcase				When alarm_schedule_noti_once_at_date is successful and returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_noti_once_at_date_p(void)
{
	START_TEST;

	struct tm stdate;
	time_t t;
	notification_h hNoti = NULL;
	int alarmId = -1;
	
	time(&t);
	t += 10;
	localtime_r(&t, &stdate);
	
	hNoti = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNoti,"notification_create");
	
	int nRet = notification_set_text(hNoti, NOTIFICATION_TEXT_TYPE_TITLE, "notification alarm", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", AlarmGetError(nRet), notification_free(hNoti));
	
	//Target API
	nRet = alarm_schedule_noti_once_at_date(hNoti, &stdate, &alarmId);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_noti_once_at_date", AlarmGetError(nRet), notification_free(hNoti));
	
	if(stdate.tm_sec < 0 || alarmId < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_noti_once_at_date returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}

	notification_free(hNoti);
	alarm_cancel_all();
	
	return 0;
}

//& type: auto
//& purpose: Sets an alarm to be triggered after a specific time.
/**
* @testcase 			ITc_alarm_schedule_noti_after_delay_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets an alarm to be triggered after a specific time
* @scenario				Sets an alarm to be triggered after a specific time
* @apicovered			notification_create, notification_set_text, alarm_schedule_noti_after_delay, notification_free
* @passcase				When alarm_schedule_noti_after_delay is successful and  returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_noti_after_delay_p(void)
{
	START_TEST;

	notification_h hNoti = NULL;
	int alarmId = -1;
	int nDelay = 1;
	int nPeriod = 1;
	
	hNoti = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNoti,"notification_create");
	
	int nRet = notification_set_text(hNoti, NOTIFICATION_TEXT_TYPE_TITLE, "notification alarm", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", AlarmGetError(nRet), notification_free(hNoti));
	
	//Target API
	nRet = alarm_schedule_noti_after_delay(hNoti, nDelay, nPeriod, &alarmId);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_noti_after_delay", AlarmGetError(nRet), notification_free(hNoti));
	
	if(alarmId < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_noti_after_delay returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}

	notification_free(hNoti);
	alarm_cancel_all();
	
	return 0;
}

//& type: auto
//& purpose: Sets an notification alarm to be triggered after a specific time.
/**
* @testcase 			ITc_alarm_schedule_noti_once_after_delay_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets an notification alarm to be triggered after a specific time
* @scenario				Sets an notification alarm to be triggered after a specific time
* @apicovered			notification_create, notification_set_text, alarm_schedule_noti_once_after_delay, notification_free
* @passcase				When alarm_schedule_noti_once_after_delay is successful and  returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_noti_once_after_delay_p(void)
{
	START_TEST;

	notification_h hNoti = NULL;
	int alarmId = -1;
	int nDelay = 1;
	
	hNoti = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNoti,"notification_create");
	
	int nRet = notification_set_text(hNoti, NOTIFICATION_TEXT_TYPE_TITLE, "notification alarm", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", AlarmGetError(nRet), notification_free(hNoti));
	
	//Target API
	nRet = alarm_schedule_noti_once_after_delay(hNoti, nDelay, &alarmId);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_noti_once_after_delay", AlarmGetError(nRet), notification_free(hNoti));
	
	if(alarmId < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_noti_once_after_delay returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}

	notification_free(hNoti);
	alarm_cancel_all();
	
	return 0;
}

//& type: auto
//& purpose: Sets an notification to be triggered periodically, starting at a specific time.
/**
* @testcase 			ITc_alarm_schedule_noti_with_recurrence_week_flag_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Sets an notification to be triggered periodically, starting at a specific time
* @scenario				Sets an notification to be triggered periodically, starting at a specific time
* @apicovered			notification_create, notification_set_text, alarm_schedule_noti_with_recurrence_week_flag, notification_free
* @passcase				When alarm_schedule_noti_with_recurrence_week_flag is successful and  returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_schedule_noti_with_recurrence_week_flag_p(void)
{
	START_TEST;

	struct tm stdate;
	time_t t;
	notification_h hNoti = NULL;
	int alarmId = -1;
	
	time(&t);
	localtime_r(&t, &stdate);
	stdate.tm_sec += 5;
	
	hNoti = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNoti,"notification_create");
	
	int nRet = notification_set_text(hNoti, NOTIFICATION_TEXT_TYPE_TITLE, "notification alarm", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", AlarmGetError(nRet), notification_free(hNoti));
	
	//Target API
	nRet = alarm_schedule_noti_with_recurrence_week_flag(hNoti, &stdate, ALARM_WEEK_FLAG_TUESDAY, &alarmId);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_noti_with_recurrence_week_flag", AlarmGetError(nRet), notification_free(hNoti));
	
	if( alarmId < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_noti_with_recurrence_week_flag returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}

	notification_free(hNoti);
	alarm_cancel_all();
	
	return 0;
}

//& type: auto
//& purpose: Gets the notification to be posted when the the alarm is triggered.
/**
* @testcase 			ITc_alarm_get_notification_p
* @since_tizen			3.0
* @author				SRID(a.pandia1)
* @reviewer			 	SRID(shobhit.v)
* @type 				auto
* @description			Gets the notification to be posted when the the alarm is triggered
* @scenario				Gets the notification to be posted when the the alarm is triggered
* @apicovered			notification_create, notification_set_text, alarm_schedule_noti_after_delay, alarm_get_notification, notification_get_text, notification_free
* @passcase				When alarm_get_notification is successful and  returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_get_notification_p(void)
{
	START_TEST;

	notification_h hNoti = NULL;
	notification_h hNotiRet = NULL;
	int alarmId = -1;
	int nDelay = 1;
	int nPeriod = 1;
	char *pszText = NULL;
	
	hNoti = notification_create(NOTIFICATION_TYPE_NOTI);
	CHECK_HANDLE(hNoti,"notification_create");
	
	int nRet = notification_set_text(hNoti, NOTIFICATION_TEXT_TYPE_TITLE, "notification alarm", NULL, NOTIFICATION_VARIABLE_TYPE_NONE);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_set_text", AlarmGetError(nRet), notification_free(hNoti));
	
	//Target API
	nRet = alarm_schedule_noti_after_delay(hNoti, nDelay, nPeriod, &alarmId);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_noti_after_delay", AlarmGetError(nRet), notification_free(hNoti));
	
	if(alarmId < 0)
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_noti_after_delay returned invalid output parameter\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}

	nRet = alarm_get_notification(alarmId, &hNotiRet);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_get_notification", AlarmGetError(nRet), notification_free(hNoti));
	CHECK_HANDLE(hNotiRet,"alarm_get_notification");
	
	nRet = notification_get_text(hNotiRet, NOTIFICATION_TEXT_TYPE_TITLE, &pszText);
	PRINT_RESULT_CLEANUP(NOTIFICATION_ERROR_NONE, nRet, "notification_get_text", AlarmGetError(nRet), notification_free(hNoti));
	if(strcmp(pszText, "notification alarm") != 0)
	{
		FPRINTF("[Line : %d][%s] notification_get_text returned invalid text\\n", __LINE__, API_NAMESPACE);
		notification_free(hNoti);
		return 1;
	}
	
	notification_free(hNoti);
	alarm_cancel_all();
	
	return 0;
}

//& type: auto
//& purpose: Sets an alarm to be triggered after a specific time and update alarm delay.
/**
* @testcase 			ITc_alarm_update_delay_p
* @since_tizen			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(nibha.sharma)
* @type 				auto
* @description			Sets an alarm to be triggered after a specific time and update alarm delay.
* @scenario			Calls the alarm_update_delay() and then checks the return value.
*				Removes the registerted alarms.
* @apicovered			alarm_update_delay
* @passcase			When alarm_update_delay is successful and  returns correct value.
* @failcase			If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_update_delay_p(void)
{
	START_TEST;

	app_control_h hAppControl = NULL;
	char *pszPackage = "org.tizen.globalapp";

	int nRet = ALARM_ERROR_NONE;
	int nAlarmID = -1;
	int nDelay = 120;		// 2 Minutes
	int nPeriod = 30;		// 0.5 minute

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	if ( hAppControl == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create returned invalid app id = %d\\n", __LINE__, API_NAMESPACE, hAppControl);
		return 1;
	}

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_after_delay returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_update_delay(nAlarmID, nPeriod);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_update_delay", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));
	 
	nRet = alarm_cancel(nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
 
	return 0;
}

//& type: auto
//& purpose: Sets an alarm to be triggered on specific date (specific time) and update alarm date(new time).
/**
* @testcase 			ITc_alarm_update_date_p
* @since_tizen			4.0
* @author				SRID(j.abhishek)
* @reviewer			 	SRID(nibha.sharma)
* @type 				auto
* @description			Sets a notification alarm to be triggered at a specific time
* @scenario				Sets an alarm to be triggered after a specific time and update alarm delay.
* @apicovered			alarm_update_date
* @passcase				When alarm_update_date is successful and  returns correct value.
* @failcase				If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_update_date_p(void)
{
	START_TEST;

	app_control_h hAppControl = NULL;
	char *pszPackage = "org.tizen.globalapp";

	struct tm stDate1;
	struct tm stDate2;
	time_t tNow;

	int nAlarmID = -1;
	int nRet = ALARM_ERROR_NONE;

	time(&tNow);
	tNow += 10;
	localtime_r(&tNow, &stDate1);
	tNow += 10;
	localtime_r(&tNow, &stDate2);
	
	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	if ( hAppControl == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create returned invalid app id = %d\\n", __LINE__, API_NAMESPACE, hAppControl);
		return 1;
	}

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = alarm_schedule_once_at_date(hAppControl, &stDate1, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_once_at_date", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_once_at_date returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_update_date(nAlarmID, &stDate2);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_update_date", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	nRet = alarm_cancel_all();
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel_all", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
 
	return 0;
}

//& type: auto
//& purpose: Sets an alarm to be triggered after a specific time and update it with the specific time period.
/**
* @testcase 			ITc_alarm_update_period_p
* @since_tizen			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(nibha.sharma)
* @type 				auto
* @description			Sets an alarm to be triggered after a specific time and update alarm delay.
* @scenario			Calls the alarm_update_period() and then checks the return value.
*				Removes the registerted alarms.
* @apicovered			alarm_update_period
* @passcase			When alarm_update_period is successful and  returns correct value.
* @failcase			If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_update_period_p(void)
{

	START_TEST;

	app_control_h hAppControl = NULL;
	char *pszPackage = "org.tizen.globalapp";

	int nRet = ALARM_ERROR_NONE;
	int nAlarmID = -1;
	int nDelay = 10;		// 10 Seconds
	int nPeriod = 100;		// 100 Seconds

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	if ( hAppControl == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create returned invalid app id = %d\\n", __LINE__, API_NAMESPACE, hAppControl);
		return 1;
	}

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = alarm_schedule_after_delay(hAppControl, nDelay, nPeriod, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_after_delay", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_after_delay returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_update_period(nAlarmID, nPeriod);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_update_period", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));

	nRet = alarm_cancel_all();
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel_all", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
 
	return 0;
}

//& type: auto
//& purpose: Sets an alarm to be triggered repeatedly on specific day of a week (specific time) and then update day of the week.
/**
* @testcase 			ITc_alarm_update_week_flag_p
* @since_tizen			4.0
* @author			SRID(j.abhishek)
* @reviewer			SRID(nibha.sharma)
* @type 			auto
* @description			Sets an alarm to be triggered after a specific time and update alarm delay.
* @scenario			Calls the alarm_update_week_flag() and then checks the return value.
*				Removes the registerted alarms.
* @apicovered			alarm_update_week_flag
* @passcase			When alarm_update_period is successful and returns correct value.
* @failcase			If target API fails or returns incorrect value.
* @precondition			None
* @postcondition		None
*/
int ITc_alarm_update_week_flag_p(void)
{
	START_TEST;

	app_control_h hAppControl = NULL;
	char *pszPackage = "org.tizen.globalapp";

	struct tm stDate;
	time_t tNow;

	int nAlarmID = -1;
	int nRet = ALARM_ERROR_NONE;

	time(&tNow);
	localtime_r(&tNow, &stDate);
	stDate.tm_sec += 30;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	if ( hAppControl == NULL )
	{
		FPRINTF("[Line : %d][%s] app_control_create returned invalid app id = %d\\n", __LINE__, API_NAMESPACE, hAppControl);
		return 1;
	}

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, ALARM_WEEK_FLAG_MONDAY, &nAlarmID);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet), app_control_destroy(hAppControl));

	if ( nAlarmID < 0 )
	{
		FPRINTF("[Line : %d][%s] alarm_schedule_with_recurrence_week_flag returned invalid alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);
		app_control_destroy(hAppControl);
		return 1;
	}

	nRet = alarm_update_week_flag(nAlarmID, ALARM_WEEK_FLAG_TUESDAY);
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_update_week_flag", AlarmGetError(nRet),  alarm_cancel(nAlarmID);app_control_destroy(hAppControl));
	 
	nRet = alarm_cancel_all();
	PRINT_RESULT_CLEANUP(ALARM_ERROR_NONE, nRet, "alarm_cancel_all", AlarmGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_destroy(hAppControl);
	PRINT_RESULT_NORETURN(APP_CONTROL_ERROR_NONE, nRet, "app_control_destroy", AppControlGetError(nRet));
 
	return 0;
}

/** @} */
/** @} */
