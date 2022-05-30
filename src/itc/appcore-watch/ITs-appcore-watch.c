//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-appcore-watch-common.h"

bool g_bAppcoreWatchFeatureSupported = false;

//& set: AppcoreWatch

/**
 * @function 		ITs_appcore_watch_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_appcore_watch_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][appcore_watch_ITC] TEST SUIT start-up: ITs_Appcore_Watch_p\\n", __LINE__);
#endif
	IS_FEATURE_SUPPORTED(WATCH_APP_FEATURE, g_bAppcoreWatchFeatureSupported, API_NAMESPACE);

	return;
}

/**
 * @function 		ITs_appcore_watch_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */ 
void ITs_appcore_watch_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][appcore_watch_ITC] TEST SUIT clean-up: ITs_Appcore_Watch_p\\n", __LINE__);
#endif
	return;
}


//& purpose: Adds and removes the system event handler
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_app_add_remove_event_handler_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Adds and removes the system event handler
 * @scenario				Add the system event handler
 *							Remove the registered event handler
 * @apicovered				watch_app_add_event_handler, watch_app_remove_event_handler
 * @passcase				When watch_app_add_event_handler and watch_app_remove_event_handler is successful.
 * @failcase				If target API watch_app_add_event_handler or watch_app_remove_event_handler or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_app_add_remove_event_handler_p(void)
{
	START_TEST;
	
	app_event_handler_h handler;

	// Target API
	int nRet = watch_app_add_event_handler(&handler, APP_EVENT_LOW_MEMORY, (app_event_cb) event_callback, NULL);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_app_add_event_handler", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_add_event_handler", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_app_remove_event_handler(handler);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_remove_event_handler", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the current time and then deletes the watch time handle to releases all its resources
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_current_time_delete_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the current time and then deletes the watch time handle to releases all its resources
 * @scenario				Get the current time
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_current_time, watch_time_delete
 * @passcase				When watch_time_get_current_time and watch_time_delete is successful.
 * @failcase				If target API watch_time_get_current_time or watch_time_delete or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_current_time_delete_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};

	// Target API
	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the year info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_year_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the year info
 * @scenario				Get the current time
 *							Get the year info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_year
 * @passcase				When watch_time_get_year is successful.
 * @failcase				If target API watch_time_get_year or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_year_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int year;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	// Target API
	nRet = watch_time_get_year(watch_time, &year);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_year", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( year < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_year returned returned invalid value = %d\\n", __LINE__, year);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the month info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_month_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the month info
 * @scenario				Get the current time
 *							Get the month info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_month
 * @passcase				When watch_time_get_month is successful.
 * @failcase				If target API watch_time_get_month or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_month_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int month;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_get_month(watch_time, &month);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_month", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( month < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_month returned returned invalid value = %d\\n", __LINE__, month);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the day info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_day_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the day info
 * @scenario				Get the current time
 *							Get the day info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_day
 * @passcase				When watch_time_get_day is successful.
 * @failcase				If target API watch_time_get_day or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_day_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int day;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_get_day(watch_time, &day);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_day", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( day < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_day returned returned invalid value = %d\\n", __LINE__, day);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the day of week info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_day_of_week_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the day of week info
 * @scenario				Get the current time
 *							Get the day of week info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_day_of_week
 * @passcase				When watch_time_get_day_of_week is successful.
 * @failcase				If target API watch_time_get_day_of_week or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_day_of_week_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int day_of_week;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_get_day_of_week(watch_time, &day_of_week);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_day_of_week", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( day_of_week < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_day_of_week returned returned invalid value = %d\\n", __LINE__, day_of_week);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the hour info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_hour_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the hour info
 * @scenario				Get the current time
 *							Get the hour info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_hour
 * @passcase				When watch_time_get_hour is successful.
 * @failcase				If target API watch_time_get_hour or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_hour_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int hour;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	
	// Target API
	nRet = watch_time_get_hour(watch_time, &hour);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_hour", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( hour < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_hour returned returned invalid value = %d\\n", __LINE__, hour);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the hour info in 24-hour presentation
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_hour24_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the hour info in 24-hour presentation
 * @scenario				Get the current time
 *							Get the hour info in 24-hour presentation
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_hour24
 * @passcase				When watch_time_get_hour24 is successful.
 * @failcase				If target API watch_time_get_hour24 or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_hour24_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int hour24;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_get_hour24(watch_time, &hour24);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_hour24", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( hour24 < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_hour24 returned returned invalid value = %d\\n", __LINE__, hour24);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

//& purpose: Gets the minute info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_minute_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the minute info
 * @scenario				Get the current time
 *							Get the minute info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_minute
 * @passcase				When watch_time_get_minute is successful.
 * @failcase				If target API watch_time_get_minute or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_minute_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int minute;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	// Target API
	nRet = watch_time_get_minute(watch_time, &minute);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_minute", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( minute < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_minute returned returned invalid value = %d\\n", __LINE__, minute);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the second info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_second_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the second info
 * @scenario				Get the current time
 *							Get the second info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_second
 * @passcase				When watch_time_get_second is successful.
 * @failcase				If target API watch_time_get_second or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_second_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int second;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	// Target API
	nRet = watch_time_get_second(watch_time, &second);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_second", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( second < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_second returned returned invalid value = %d\\n", __LINE__, second);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the millisecond info
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_millisecond_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the millisecond info
 * @scenario				Get the current time
 *							Get the millisecond info
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_millisecond
 * @passcase				When watch_time_get_millisecond is successful.
 * @failcase				If target API watch_time_get_millisecond or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_millisecond_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	int millisecond;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	// Target API
	nRet = watch_time_get_millisecond(watch_time, &millisecond);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_millisecond", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	if ( millisecond < 0 )
	{
		FPRINTF("[Line : %d][appcore_watch_ITC] watch_time_get_millisecond returned returned invalid value = %d\\n", __LINE__, millisecond);

		nRet = watch_time_delete(watch_time);
		if(nRet != APP_ERROR_NONE)
		{
			FPRINTF("[Line : %d][%s] watch_time_delete Failed and returnd Error\\n", __LINE__, API_NAMESPACE);
		}
		return 1;
	}

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the UTC time
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_utc_time_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the UTC time
 * @scenario				Get the current time
 *							Get the UTC time
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_utc_time
 * @passcase				When watch_time_get_utc_time is successful.
 * @failcase				If target API watch_time_get_utc_time or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_utc_time_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	
	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	struct tm *utc_time = calloc(1, sizeof(struct tm));
	
	// Target API
	nRet = watch_time_get_utc_time(watch_time, utc_time);
	FREE_MEMORY(utc_time);

	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_utc_time", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));
	
	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the UTC timestamp
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_utc_timestamp_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the UTC timestamp
 * @scenario				Get the current time
 *							Get the UTC timestamp
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_utc_timestamp
 * @passcase				When watch_time_get_utc_timestamp is successful.
 * @failcase				If target API watch_time_get_utc_timestamp or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_utc_timestamp_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	
	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	time_t *time_stamp = calloc(1, sizeof(time_t));

	// Target API
	nRet = watch_time_get_utc_timestamp(watch_time, time_stamp);
	FREE_MEMORY(time_stamp);

	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_utc_timestamp", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));
	
	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose: Gets the ID of timezone for the watch_time handle
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_time_zone_p
 * @since_tizen 			2.3.1
 * @author            		SRID(shekhar1.s)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Gets the ID of timezone for the watch_time handle
 * @scenario				Get the current time
 *							Get the ID of timezone for the watch_time handle
 *							Delete the watch time handle and releases all its resources
 * @apicovered				watch_time_get_time_zone
 * @passcase				When watch_time_get_time_zone is successful.
 * @failcase				If target API watch_time_get_time_zone or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_time_zone_p(void)
{
	START_TEST;
	
	watch_time_h watch_time = {0,};
	
	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	
	char* timezone = (char*) malloc(TIMEZONE_BUFFER_MAX * sizeof(char));

	// Target API
	nRet = watch_time_get_time_zone(watch_time, &timezone);
	FREE_MEMORY(timezone);

	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_time_zone", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));
	
	return 0;
}

//& purpose:  Sets and Gets the type of periodic ambient tick. 
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_app_set_get_ambient_tick_type_p
 * @since_tizen 			2.3.2
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Sets and Gets the type of periodic ambient tick. 
 * @scenario				Sets and Gets the type of periodic ambient tick. 							
 * @apicovered				watch_app_set_ambient_tick_type and watch_app_get_ambient_tick_type
 * @passcase				When watch_app_set_ambient_tick_type and watch_app_get_ambient_tick_type are successful.
 * @failcase				If target APIs or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_app_set_get_ambient_tick_type_p(void)
{
	START_TEST;
	
	watch_app_ambient_tick_type_e eSetType[]={ 
				 WATCH_APP_AMBIENT_TICK_NO_TICK, 
				 WATCH_APP_AMBIENT_TICK_EVERY_MINUTE, 
				 WATCH_APP_AMBIENT_TICK_EVERY_FIVE_MINUTES, 
				 WATCH_APP_AMBIENT_TICK_EVERY_FIFTEEN_MINUTES, 
				 WATCH_APP_AMBIENT_TICK_EVERY_THIRTY_MINUTES, 
				 WATCH_APP_AMBIENT_TICK_EVERY_HOUR, 
				 WATCH_APP_AMBIENT_TICK_EVERY_THREE_HOURS, 
				 WATCH_APP_AMBIENT_TICK_EVERY_SIX_HOURS, 
				 WATCH_APP_AMBIENT_TICK_EVERY_TWELVE_HOURS, 
				 WATCH_APP_AMBIENT_TICK_EVERY_DAY};

	int nEnumCount = sizeof(eSetType) / sizeof(eSetType[0]);
	watch_app_ambient_tick_type_e eGetType;
	int nEnumLoopCount;
	for (nEnumLoopCount = 0; nEnumLoopCount < nEnumCount; nEnumLoopCount++ )
	{
		// Target API		 
		int nRet = watch_app_set_ambient_tick_type(eSetType[nEnumLoopCount]); 
		CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_app_set_ambient_tick_type", AppcoreWatchGetError(nRet));
		PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_set_ambient_tick_type", AppcoreWatchGetError(nRet));
	
		// Target API
		nRet = watch_app_get_ambient_tick_type(&eGetType); 
		PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_get_ambient_tick_type", AppcoreWatchGetError(nRet));

		if(eSetType[nEnumLoopCount]!=eGetType)
		{
			FPRINTF("[Line : %d][appcore_watch_ITC] Set Get value mismatch, error returned = %s\\n", __LINE__, AppcoreWatchGetError(nRet));
			return 1;
		}
	}
	
	return 0;
}

//& purpose:  Sets and Gets the time tick type. 
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_app_set_get_time_tick_frequency_p
 * @since_tizen 			3.0
 * @author            		SRID(shilpa.j)
 * @reviewer         		SRID(a.pandia1)
 * @type 					auto
 * @description				Sets and Gets the type of periodic ambient tick. 
 * @scenario				Sets and Gets the type of periodic ambient tick. 							
 * @apicovered				watch_app_set_ambient_tick_type and watch_app_get_ambient_tick_type
 * @passcase				When watch_app_set_ambient_tick_type and watch_app_get_ambient_tick_type are successful.
 * @failcase				If target APIs or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_app_set_get_time_tick_frequency_p(void)
{
	START_TEST;
	
	watch_app_time_tick_resolution_e eSetType[]={ 
				 WATCH_APP_TIME_TICKS_PER_SECOND, 
				 WATCH_APP_TIME_TICKS_PER_MINUTE, 
				 WATCH_APP_TIME_TICKS_PER_HOUR, 
				};
				 


	int nEnumCount = sizeof(eSetType) / sizeof(eSetType[0]);
	int nTickCount = 60;
	int nTick;
	int nEnumLoopCount;
	watch_app_time_tick_resolution_e egettime_tick;
	
	for (nEnumLoopCount = 0; nEnumLoopCount < nEnumCount; nEnumLoopCount++ )
	{
		// Target API		 
		int nRet = watch_app_set_time_tick_frequency(nTickCount,eSetType[nEnumLoopCount]); 
		CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_app_set_time_tick_frequency", AppcoreWatchGetError(nRet));
		PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_set_time_tick_frequency", AppcoreWatchGetError(nRet));
	
		// Target API
		nRet = watch_app_get_time_tick_frequency(&nTick,&egettime_tick);
		PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_app_get_time_tick_frequency", AppcoreWatchGetError(nRet));

		if(eSetType[nEnumLoopCount]!=egettime_tick || nTick !=nTickCount  )
		{
			FPRINTF("[Line : %d][appcore_watch_ITC] Set Get value mismatch, error returned = %s   %d\\n", __LINE__, AppcoreWatchGetError(nRet),nTick);
			return 1;
		}
	}
	
	return 0;
}

//& purpose: Gets the daylight saving time status.
//& type: auto
/**
 * @testcase 				ITc_appcore_watch_watch_time_get_dst_status_p
 * @since_tizen 			4.0
 * @author            		SRID(nibha.sharma)
 * @reviewer         		SRID(shobhit.v)
 * @type 					auto
 * @description				Gets the daylight saving time status.
 * @scenario				Gets the daylight saving time status.
 * @apicovered				watch_time_get_dst_status
 * @passcase				When watch_time_get_dst_status is successful.
 * @failcase				If target API watch_time_get_dst_status or any supporting API fails.
 * @precondition			NA
 * @postcondition			NA
 */
int ITc_appcore_watch_watch_time_get_dst_status_p(void)
{
	START_TEST;

	watch_time_h watch_time = {0,};
	bool bStatus;

	int nRet = watch_time_get_current_time(&watch_time);
	CHECK_SUPPORT(APP_ERROR_NOT_SUPPORTED, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_get_current_time", AppcoreWatchGetError(nRet));

	// Target API
	nRet = watch_time_get_dst_status(watch_time, &bStatus);
	PRINT_RESULT_CLEANUP(APP_ERROR_NONE, nRet, "watch_time_get_dst_status", AppcoreWatchGetError(nRet), watch_time_delete(watch_time));

	nRet = watch_time_delete(watch_time);
	PRINT_RESULT(APP_ERROR_NONE, nRet, "watch_time_delete", AppcoreWatchGetError(nRet));

	return 0;
}

