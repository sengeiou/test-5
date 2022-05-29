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

//& set: CalendarServiceConnect

/**
* @function 		ITs_calendar_service1_startup
* @description	 	Called before each test, connects to the calendar service
* @parameter		NA
* @return 			NA
*/ 
void ITs_calendar_service1_startup(void)
{
	struct stat stBuff;   
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Calendar_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		ITs_calendar_service1_cleanup
* @description	 	Called after each test, disconnects to the calendar service
* @parameter		NA
* @return 			NA
*/ 
void ITs_calendar_service1_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Calendar_Service_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup itc-calendar-service2-testcases
*  @brief 		Integration testcases for module calendar-service2
*  @ingroup 	itc-calendar-service2
*  @{
*/

//&purpose	Connects and disconnects the calendar service
//&type		Auto
/**
* @testcase 			ITc_calendar_connect_disconnect_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects and disconnects the calendar service
* @scenario				Connects to the calendar service\n
* 						Disconnects from the calendar service
* @apicovered			calendar_connect,  calendar_disconnect
* @passcase				CALENDAR_ERROR_NONE returned by calendar_connect and calendar_disconnect.
* @failcase				If target APIs calendar_connect or calendar_disconnect fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_calendar_connect_disconnect_p(void)
{
	START_TEST_NO_CHECK;

	// Target APIs
	bool bCalendarIssupportedFeature = TCTCheckSystemInfoFeatureSupported(CALENDAR_FEATURE, API_NAMESPACE);
	int nRetVal = calendar_connect();
	if ( false == bCalendarIssupportedFeature)
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d] [%s] Feature Mismatch so Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d] [%s] calendar feature not supported,  Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_connect", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_disconnect();
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_disconnect", CalendarServiceGetError(nRetVal));

	return 0;
}

//&purpose	Connects and disconnects the calendar service on thread
//&type		Auto
/**
* @testcase 			ITc_calendar_connect_disconnect_on_thread_p
* @since_tizen 			2.3
* @author				SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects and disconnects the calendar service on thread
* @scenario				Connects to the calendar service on thread\n
* 						Disconnects from the calendar service on thread
* @apicovered			calendar_connect_on_thread,  calendar_disconnect_on_thread
* @passcase				CALENDAR_ERROR_NONE returned by calendar_connect_on_thread and calendar_disconnect_on_thread.
* @failcase				If target APIs calendar_connect_on_thread or calendar_disconnect_on_thread fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_calendar_connect_disconnect_on_thread_p(void)
{
	START_TEST_NO_CHECK;
	bool bCalendarIssupportedFeature = TCTCheckSystemInfoFeatureSupported(CALENDAR_FEATURE, API_NAMESPACE);
	int nRetVal = calendar_connect_on_thread();
	if ( false == bCalendarIssupportedFeature)
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d] [%s] Feature Mismatch so Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d] [%s] calendar feature not supported,  Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	// Target APIs
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_connect_on_thread", CalendarServiceGetError(nRetVal));

	nRetVal = calendar_disconnect_on_thread();
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_disconnect_on_thread", CalendarServiceGetError(nRetVal));

	return 0;
}

//&purpose	Connects to the calendar service with flag
//&type		Auto
/**
* @testcase 			ITc_calendar_connect_with_flags_p
* @since_tizen 			2.3
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Connects to the calendar service with flag
* @scenario				Connects to the calendar service with flag\n
* 						Disconnects from the calendar service
* @apicovered			calendar_connect_with_flags,  calendar_disconnect
* @passcase				CALENDAR_ERROR_NONE returned by calendar_connect_with_flags
* @failcase				If target APIs calendar_connect_with_flags fails
* @precondition			NA
* @postcondition		Disconnects from the calendar service
*/
int ITc_calendar_connect_with_flags_p(void)
{
	START_TEST_NO_CHECK;
	bool bCalendarIssupportedFeature = TCTCheckSystemInfoFeatureSupported(CALENDAR_FEATURE, API_NAMESPACE);
	// Target APIs
	int nRetVal = calendar_connect_with_flags(CALENDAR_CONNECT_FLAG_RETRY);
	if ( false == bCalendarIssupportedFeature)
	{
		if ( nRetVal != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d] [%s] Feature Mismatch so Leaving test\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d] [%s] calendar feature not supported,  Leaving test\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_connect_with_flags", CalendarServiceGetError(nRetVal));

	//Postcondition
	nRetVal = calendar_disconnect();
	PRINT_RESULT(CALENDAR_ERROR_NONE, nRetVal, "calendar_disconnect", CalendarServiceGetError(nRetVal));

	return 0;
}
/** @} */ 
/** @} */
