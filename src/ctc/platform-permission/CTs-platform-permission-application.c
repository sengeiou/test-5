#include "CTs-platform-permission-common.h"
#include "app.h"
#include "app_alarm.h"
#include "app_control.h"
#include "app_preference.h"
#include "app_resource_manager.h"
#include "app_event.h"
#include "bundle.h"

#include <glib.h>
#include <glib-object.h>
#define SET_PACKAGE_LAUNCH			"org.tizen.testapplication"

int g_bAppControlSendLaunchRequest = false;
int g_AlarmIDValueReceived = -1;
int g_AlarmRegisteredReceived = 0;
bool g_bUserDataMismatch_appControl = false;
bool g_bUserDataMismatch_alarm = false;
bool g_bCallBackHit_appControl = false;
bool g_bCallBackHit_alarm = false;
char* AlarmGetError(int nRet);
void *g_pUserData_alarm = "user_data_1";
void *g_pUserData_appControl = "user_data_1";

GMainLoop *g_pApplicationMainLoop;

#define RUN_POLLING_LOOP {\
	g_pApplicationMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, Timeout, g_pApplicationMainLoop);\
	g_main_loop_run(g_pApplicationMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pApplicationMainLoop = NULL;\
}

/**
* @function 		AppControlGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AppControlGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case APP_CONTROL_ERROR_NONE:					szErrorVal = "APP_CONTROL_ERROR_NONE";break;
	case APP_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "APP_CONTROL_ERROR_INVALID_PARAMETER";break;
	case APP_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "APP_CONTROL_ERROR_OUT_OF_MEMORY";break;
	case APP_CONTROL_ERROR_APP_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_APP_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_NOT_FOUND:			szErrorVal = "APP_CONTROL_ERROR_KEY_NOT_FOUND";break;
	case APP_CONTROL_ERROR_KEY_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_KEY_REJECTED";break;
	case APP_CONTROL_ERROR_INVALID_DATA_TYPE:		szErrorVal = "APP_CONTROL_ERROR_INVALID_DATA_TYPE";break;
	case APP_CONTROL_ERROR_LAUNCH_REJECTED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_REJECTED";break;
	case APP_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "APP_CONTROL_ERROR_PERMISSION_DENIED";break;
	case APP_CONTROL_ERROR_LAUNCH_FAILED:			szErrorVal = "APP_CONTROL_ERROR_LAUNCH_FAILED";break;
	case APP_CONTROL_ERROR_TIMED_OUT:				szErrorVal = "APP_CONTROL_ERROR_TIMED_OUT";break;
	default:										szErrorVal = "Undefined Error";break;
	}
	return szErrorVal;
}


/**
* @function 		AlarmGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* AlarmGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case ALARM_ERROR_NONE:					szErrorVal = "ALARM_ERROR_NONE";break;
	case ALARM_ERROR_INVALID_PARAMETER:		szErrorVal = "ALARM_ERROR_INVALID_PARAMETER";break;
	case ALARM_ERROR_INVALID_TIME:			szErrorVal = "ALARM_ERROR_INVALID_TIME";break;
	case ALARM_ERROR_INVALID_DATE:			szErrorVal = "ALARM_ERROR_INVALID_DATE";break;
	case ALARM_ERROR_CONNECTION_FAIL:		szErrorVal = "ALARM_ERROR_CONNECTION_FAIL";break;
	case ALARM_ERROR_OUT_OF_MEMORY:			szErrorVal = "ALARM_ERROR_OUT_OF_MEMORY";break;
	case ALARM_ERROR_PERMISSION_DENIED :	szErrorVal = "ALARM_ERROR_PERMISSION_DENIED";break;
	default:								szErrorVal = "Undefined Error";break;
	}

	return szErrorVal;
}

/**
* @function 		application_alarm_registered_alarm_cb
* @description	 	callback function for registered alarm
* @parameter		nAlarmID : alarm ID, user_data : user data sent to callback
* @return 			true
*/
bool application_alarm_registered_alarm_cb(int nAlarmID, void *user_data)
{
	g_bCallBackHit_alarm = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_alarm) != 0)
	{
		g_bUserDataMismatch_alarm = true;
	}

	FPRINTF("[Line : %d][%s]application_alarm_registered_alarm_cb invoked;alarm id = %d\\n", __LINE__, API_NAMESPACE, nAlarmID);

	g_AlarmIDValueReceived = nAlarmID;
	++g_AlarmRegisteredReceived;
	return true;
}

/**
* @function 		application_app_control_reply_cb
* @description	 	callback function for app control reply
* @parameter		hRequest : handle for app control request, hReply : app control handle, eResult : result, user_data : user data sent to callback
* @return 			false
*/
void application_app_control_reply_cb(app_control_h hRequest, app_control_h hReply, app_control_result_e eResult, void *user_data)
{
	g_bCallBackHit_appControl = true;
	if(strcmp((char *)user_data,(char *)g_pUserData_appControl) != 0)
	{
		g_bUserDataMismatch_appControl = true;
	}

	g_bAppControlSendLaunchRequest = true;
	FPRINTF("[Line : %d][%s] app_control_reply_callback invoked, error returned = %d\\n", __LINE__, API_NAMESPACE, (int)eResult);
	
	if (g_pApplicationMainLoop)
	{
		g_main_loop_quit(g_pApplicationMainLoop);
		g_pApplicationMainLoop = NULL;
	}
}
/**
* @function         CTs_platform_permission_Application_startup
* @description      Called before each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_Application_startup(void)
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
    FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_platform_permission_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function         CTs_platform_permission_Application_cleanup
* @description      Called after each test
* @parameter        NA
* @return           NA
*/
void CTs_platform_permission_Application_cleanup(void)
{
#if DEBUG
    FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_platform_permission_Application_p\\n", __LINE__, API_NAMESPACE);
#endif
    return;
}

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_schedule_once_after_delay
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create AppControl\n
*					Set Alarm after Delay\n
*					Check Alarm ID\n
*					Destroy AppControl				
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_once_after_delay, alarm_cancel
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_schedule_once_after_delay(void)
{
	START_TEST;
	int nRet = -1;
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min

	//Target API
	nRet = alarm_schedule_once_after_delay(hAppControl, nDelay, &nAlarmID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_once_after_delay", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);

	app_control_destroy(hAppControl);
	
	return 0;
}

#ifdef WEARABLE      //Starts WEARABLE

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_cancel_all
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			cancel all alarm
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_once_after_delay, alarm_cancel
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_cancel_all(void)
{
	START_TEST;
	int nRet = -1;
	
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	
	nRet = alarm_schedule_after_delay(hAppControl, nDelay,nDelay, &nAlarmID);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_after_delay", AlarmGetError(nRet),app_control_destroy(hAppControl));

	if( nAlarmID > 0 )
	{
		//Target API
		nRet = alarm_cancel_all();
		PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_cancel_all", AlarmGetError(nRet),app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);	
	}
	app_control_destroy(hAppControl);
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/alarm.get privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmGet_alarm_get_app_control
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the app_control to be invoked when the the alarm is triggered. 
* @apicovered		Call alarm_schedule_once_after_delay alarm_get_app_control
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmGet_alarm_get_app_control(void)
{
	START_TEST;	
	int nRet = -1;
	
	
	app_control_h hAppControl;
	app_control_h hAppControlReceived;
	
	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, SET_PACKAGE_LAUNCH);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min
	nRet = alarm_schedule_after_delay(hAppControl, nDelay, nDelay, &nAlarmID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_once_after_delay", AppControlGetError(nRet),app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	
	if(nAlarmID>0)
	{
		nRet = alarm_get_app_control(nAlarmID, &hAppControlReceived);
		PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_get_app_control", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	}
	
	alarm_cancel(nAlarmID);
	app_control_destroy(hAppControl);
	
	return 0;
}

#endif  //End WEARABLE

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_date
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Get alarm
* @apicovered		Call app_control_create, app_control_destroy, alarm_get_scheduled_date
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_date(void)
{
	START_TEST;
	int nRet = -1;
	int nAlarmID = -1;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec = 30;//set sec value to 30 sec
	int nWeekday = ALARM_WEEK_FLAG_SUNDAY;
	struct tm stGetDate;
	
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, nWeekday, &nAlarmID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet),app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);

	if ( nAlarmID > 0 )
	{
		//Target API
		nRet = alarm_get_scheduled_date(nAlarmID, &stGetDate);
		PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_at_date", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl), APP_CONTROL_ERROR_NONE);
	}
	
	alarm_cancel(nAlarmID);
	app_control_destroy(hAppControl);
	
	return 0;
}

#ifdef WEARABLE	//Starts WEARABLE

//& purpose:Checking tizen.org/privilege/alarm.get privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_period
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the period of time between the recurrent alarms. 
* @apicovered		Call app_control_create, app_control_destroy, alarm_get_scheduled_period
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_period(void)
{
	START_TEST;	
	int nRet = -1;
	int nAlarmID = -1;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec = 30;//set sec value to 30 sec
	int nWeekday = ALARM_WEEK_FLAG_SUNDAY;
	int nGetPeriod = 0;
	
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	
	nRet = alarm_schedule_with_recurrence_week_flag(hAppControl, &stDate, nWeekday, &nAlarmID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet),app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	
	if ( nAlarmID > 0 )
	{
		//Target API
		nRet = alarm_get_scheduled_period(nAlarmID, &nGetPeriod);
		PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_get_scheduled_period", AlarmGetError(nRet),alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	}
	alarm_cancel(nAlarmID);
	app_control_destroy(hAppControl);
	
	return 0;
}

#endif  //End WEARABLE

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_schedule_at_date
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Set alarm to trigger at specific time			
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_at_date
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_schedule_at_date(void)
{
	START_TEST;
	int nRet = -1;
	int tid;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec += 60;//set after 1 min
	

	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));
		
	//Target API	
	nRet = alarm_schedule_at_date(hAppControl, &stDate, 0, &tid);
	app_control_destroy(hAppControl);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_at_date", AlarmGetError(nRet));
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_schedule_once_at_date
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create AppControl\n
*					Set Alarm AT DATE\n
*					Check Alarm ID\n
*					Destroy AppControl				
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_once_at_date, alarm_cancel
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_schedule_once_at_date (void)
{
	START_TEST;
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
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
	app_control_destroy(hAppControl);
	alarm_cancel(nAlarmID);
	PRINT_RESULT(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_once_at_date", AlarmGetError(nRet));
	
	return 0;
}


//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_schedule_after_delay
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create AppControl\n
*					Set Alarm schedule after delay\n
*					Check Alarm ID\n
*					Destroy AppControl				
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_after_delay, alarm_cancel
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_schedule_after_delay (void)
{
	START_TEST;
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = -1;
	int nDelay = 60;//sample 1 min

	//Target API
	nRet = alarm_schedule_after_delay(hAppControl, nDelay,nDelay, &nAlarmID);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_after_delay", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
		
	app_control_destroy(hAppControl);
	
	return 0;
}

//& purpose:Checking tizen.org/privilege/alarmset privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_schedule_with_recurrence_week_flag
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create AppControl\n
*					Set alarm schedule with recurrence week flag\n
*					Check Alarm ID\n
*					Destroy AppControl	
* @apicovered		Call app_control_create, app_control_destroy, alarm_schedule_with_recurrence_week_flag, alarm_cancel			
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_schedule_with_recurrence_week_flag (void)
{
	START_TEST;
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;

	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
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
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_schedule_with_recurrence_week_flag", AlarmGetError(nRet), alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	
	app_control_destroy(hAppControl);
	
	return 0;
}

#ifdef WEARABLE	//Starts WEARABLE

//& purpose:Checking tizen.org/privilege/alarm.get privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_recurrence_week_flag
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the recurrence days of the week. 
* @apicovered		Call app_control_create, app_control_destroy, alarm_get_scheduled_recurrence_week_flag, alarm_schedule_with_recurrence_week_flag, alarm_cancel			
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmSet_alarm_get_scheduled_recurrence_week_flag (void)
{
	START_TEST;
	app_control_h hAppControl;
	char* pszPackage = SET_PACKAGE_LAUNCH;
	int nGetWeekday; 
	
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AlarmGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, pszPackage);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	int nAlarmID = 1;
	struct tm stDate;
	alarm_get_current_time(&stDate);
	stDate.tm_sec = 30;//set sec value to 30 sec
	int nWeekday = ALARM_WEEK_FLAG_SUNDAY;
	nRet = alarm_get_scheduled_recurrence_week_flag(nAlarmID, &nGetWeekday);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_get_scheduled_recurrence_week_flag", AlarmGetError(nRet),alarm_cancel(nAlarmID);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
		
	alarm_cancel(nAlarmID);
	app_control_destroy(hAppControl);
	
	return 0;
}

#endif	//End WEARABLE

//& purpose:Checking tizen.org/privilege/appManager.Launch privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAppManagerLaunch
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Create AppControl\n
*					Set app_control launch parameter\n
*					Send the launch request\n
*					Terminate the launch request\n
*					Destroy AppControl				
* @apicovered		app_control_create, app_control_set_app_id, app_control_destroy, app_control_send_launch_request, app_control_set_operation, app_control_send_terminate_request
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAppManagerLaunch (void)
{
	START_TEST;
	app_control_h hAppControl;
	//int nTimeoutId = 0;
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, SET_PACKAGE_LAUNCH);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_enable_app_started_result_event(hAppControl);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_enable_app_started_result_event", AppControlGetError(nRet), app_control_destroy(hAppControl));
	
	nRet = app_control_send_launch_request(hAppControl, application_app_control_reply_cb, g_pUserData_appControl);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "app_control_send_launch_request", AlarmGetError(nRet), app_control_send_terminate_request(hAppControl);app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	
	app_control_send_terminate_request(hAppControl);
	app_control_destroy(hAppControl);
	
	return 0;
}


//& purpose:Checking tizen.org/privilege/alarm.get privilege
//& type: auto
/**
* @testcase			CTc_Application_PrivilegeAlarmGet_alarm_foreach_registered_alarm
* @since_tizen		2.3
* @author			SRID(gaurav.m2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Retrieves the IDs of all registered alarms by invoking a callback once for each scheduled alarm. 			
* @apicovered		app_control_create, app_control_set_app_id, app_control_destroy, alarm_foreach_registered_alarm, app_control_set_operation
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_Application_PrivilegeAlarmGet_alarm_foreach_registered_alarm (void)
{
	START_TEST;
	app_control_h hAppControl;
	
	int nRet = app_control_create(&hAppControl);
	PRINT_RESULT(APP_CONTROL_ERROR_NONE, nRet, "app_control_create", AppControlGetError(nRet));

	CHECK_HANDLE(hAppControl, "app_control_create");
	
	nRet = app_control_set_operation(hAppControl, APP_CONTROL_OPERATION_DEFAULT);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_operation", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = app_control_set_app_id(hAppControl, SET_PACKAGE_LAUNCH);
	PRINT_RESULT_CLEANUP(APP_CONTROL_ERROR_NONE, nRet, "app_control_set_app_id", AppControlGetError(nRet), app_control_destroy(hAppControl));

	nRet = alarm_foreach_registered_alarm(application_alarm_registered_alarm_cb, g_pUserData_alarm);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "alarm_foreach_registered_alarm", AlarmGetError(nRet), app_control_destroy(hAppControl),APP_CONTROL_ERROR_NONE);
	
	app_control_destroy(hAppControl);
	
	return 0;
}
