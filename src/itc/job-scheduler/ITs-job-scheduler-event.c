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
#include "ITs-job-scheduler-common.h"

//& set: JobScheduler

/**
 * @function 		ITs_job_info_event_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_info_event_startup(void)
{
	int nRet;
	g_bJobSchedulerInit = true;

	nRet = job_scheduler_init();
	if (nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to initialize job scheduler \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
		return;
	}

	nRet = job_info_create(&job_info);
	if (!job_info || nRet != JOB_ERROR_NONE)
	{
		FPRINTF("[Line: %d][%s] Failed to create job info \\n", __LINE__, API_NAMESPACE);
		g_bJobSchedulerInit = false;
	}
}

/**
 * @function 		ITs_job_info_event_cleanup
 * @description	 	Called before after test
 * @parameter		NA
 * @return 			NA
 */
void ITs_job_info_event_cleanup(void)
{
	int nRet  = JOB_ERROR_NONE;

	if (job_info)
	{
		nRet = job_info_destroy(job_info);
		PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_info_destroy", JobGetError(nRet));
		job_info = NULL;
	}

	nRet = job_scheduler_finish();
	PRINT_RESULT_NORETURN(JOB_ERROR_NONE, nRet, "job_scheduler_finish", JobGetError(nRet));
}

/** @addtogroup itc-job-scheduler
*  @brief 		Integration testcases for module job-scheduler
*  @ingroup 	itc-job-scheduler
*  @{
*/

//& type: auto
//& purpose:Sets that the WiFi must be connected to run the job.
/**
* @testcase 			ITc_job_info_set_requires_wifi_connection
* @since_tizen			4.0
* @privilege			%http://tizen.org/privilege/network.get
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets that the WiFi must be connected to run the job.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_set_requires_wifi_connection().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_set_requires_wifi_connection
* @passcase				Successffully sets that the WiFi must be connected to run the job.
* @failcase				Not able to  sets that the WiFi must be connected to run the job.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_set_requires_wifi_connection(void)
{
	START_TEST;

	g_bNetworkFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(NETWORK_FEATURE, API_NAMESPACE);

	int nRet = job_info_set_requires_wifi_connection(job_info, true);

	if (g_bNetworkFeatureNotSupported)
	{
		if(nRet != JOB_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_requires_wifi_connection", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets that the battery level must not be low to run the job.
/**
* @testcase 			ITc_job_info_set_requires_battery_not_low
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets that the battery level must not be low to run the job.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_set_requires_battery_not_low().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_set_requires_battery_not_low
* @passcase				If feature is supported than set that the battery level must not be low to run the job.
* @failcase				If feature is supported than doesn't set that the battery level must not be low to run the job.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_set_requires_battery_not_low(void)
{
	START_TEST;

	g_bBatteryFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = job_info_set_requires_battery_not_low(job_info, true);

	if (g_bBatteryFeatureNotSupported)
	{
		if(nRet != JOB_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_requires_battery_not_low", JobGetError(nRet));

	return 0;
}

//& type: auto
//& purpose: Sets that the battery must be charging to run the job.
/**
* @testcase 			ITc_job_info_set_requires_charging
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Sets that the battery must be charging to run the job.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_set_requires_charging().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the function returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_set_requires_charging
* @passcase				Successffully sets that the battery must be charging to run the job.
* @failcase				Not able to sets that the battery must be charging to run the job.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_set_requires_charging(void)
{
	START_TEST;

	g_bBatteryFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = job_info_set_requires_charging(job_info, true);

	if (g_bBatteryFeatureNotSupported)
	{
		if(nRet != JOB_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line: %d][%s] Feature is mismatch \\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line: %d][%s] Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_set_requires_charging", JobGetError(nRet));

	return 0;
}


//& type: auto
//& purpose: To add trigger event to the job info handle.
/**
* @testcase 			ITc_job_info_add_trigger_event_battery
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds the trigger event to the job info handle.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_add_trigger_event()
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the functions returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_add_trigger_event
* @passcase				Successfully triggers the battery events.
* @failcase				Not able to trigger the battery events.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_add_trigger_event_battery(void)
{
	START_TEST;

	g_bBatteryFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY;
	int nEnd = JOB_TRIGGER_EVENT_CHARGER_STATE_DISCONNECTED;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);

		if (g_bBatteryFeatureNotSupported)
		{
			if(nRet != JOB_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] Battery Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Battery Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
	}

		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: To add trigger event to the job info handle.
/**
* @testcase 			ITc_job_info_add_trigger_event
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds the trigger event to the job info handle.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_add_trigger_event().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the functions returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_add_trigger_event
* @passcase				Successfully triggers the events.
* @failcase				Not able to trigger the events.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_add_trigger_event(void)
{
	START_TEST;

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_DISPLAY_STATE_ON;
	int nEnd = JOB_TRIGGER_EVENT_EARJACK_STATE_DISCONNECTED;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);
		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	nStart = JOB_TRIGGER_EVENT_POWERSAVE_MODE_ENABLED;
	nEnd = JOB_TRIGGER_EVENT_POWERSAVE_MODE_DISABLED;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);
		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: To add trigger event to the job info handle.
/**
* @testcase 			ITc_job_info_add_trigger_event_location
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds the trigger event to the job info handle.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_add_trigger_event().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the functions returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_add_trigger_event
* @passcase				Successfully triggers the gps events.
* @failcase				Not able to trigger the gps events.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_add_trigger_event_location(void)
{
	START_TEST;

	g_bLocationFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(LOCATION_FEATURE, API_NAMESPACE);

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_GPS_STATE_DISABLED;
	int nEnd = JOB_TRIGGER_EVENT_GPS_STATE_SEARCHING;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);

		if (g_bLocationFeatureNotSupported)
		{
			if(nRet != JOB_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] GPS Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] GPS Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}

		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: To add trigger event to the job info handle.
/**
* @testcase 			ITc_job_info_add_trigger_event_usb
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds the trigger event to the job info handle.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_add_trigger_event().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the functions returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_add_trigger_event
* @passcase				Successfully triggers the usb events.
* @failcase				Not able to trigger the usb events.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_add_trigger_event_usb(void)
{
	START_TEST;

	g_bUsbFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(USB_FEATURE, API_NAMESPACE);

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_USB_STATE_CONNECTED;
	int nEnd = JOB_TRIGGER_EVENT_USB_STATE_DISCONNECTED;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);

		if (g_bUsbFeatureNotSupported)
		{
			if(nRet != JOB_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] USB Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] USB Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}

		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: To add trigger event to the job info handle.
/**
* @testcase 			ITc_job_info_add_trigger_event_network
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Adds the trigger event to the job info handle.
* @scenario				Checks whether the feature is supported or NOT.
*						Calls the job_info_add_trigger_event().
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
*						If the feature is not supported, the functions returns JOB_ERROR_NOT_SUPPORTED.
* @apicovered			TCTCheckSystemInfoFeatureSupported, job_info_add_trigger_event
* @passcase				Successfully triggers the network events.
* @failcase				Not able to trigger the network events.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_add_trigger_event_network(void)
{
	START_TEST;

	g_bNetworkFeatureNotSupported = !TCTCheckSystemInfoFeatureSupported(NETWORK_FEATURE, API_NAMESPACE);

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_WIFI_STATE_DISABLED;
	int nEnd = JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_add_trigger_event(job_info, nEvent);

		if (g_bNetworkFeatureNotSupported)
		{
			if(nRet != JOB_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line: %d][%s] Network Feature is mismatch \\n", __LINE__, API_NAMESPACE);
				return 1;
			}
			else
			{
				FPRINTF("[Line: %d][%s] Network Feature is Not Supported \\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}

		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_add_trigger_event", JobGetError(nRet));
	}

	return 0;
}

//& type: auto
//& purpose: To remove the trigger event from the job info handle.
/**
* @testcase 			ITc_job_info_remove_trigger_event
* @since_tizen			4.0
* @author				SRID(priya.kohli)
* @reviewer			 	SRID(maneesha.k)
* @type 				auto
* @description			Removes the trigger event from the job info handle.
* @scenario				Calls the job_info_remove_trigger_event() with all trigger events.
*						Checks whether the return value is JOB_ERROR_NONE or NOT.
* @apicovered			job_info_remove_trigger_event
* @passcase				Successfully removes the trigger event from the job info handle.
* @failcase				Not able to remove the trigger event from the job info handle.
* @precondition			Job Scheduler must be initialised and created.
* @postcondition		NA
*/
int ITc_job_info_remove_trigger_event(void)
{
	START_TEST;

	int nRet;
	int nStart = JOB_TRIGGER_EVENT_BATTERY_LEVEL_EMPTY;
	int nEnd = JOB_TRIGGER_EVENT_WIFI_STATE_CONNECTED;
	int nEvent;

	for (nEvent = nStart; nEvent <= nEnd; ++nEvent)
	{
		nRet = job_info_remove_trigger_event(job_info, nEvent);
		PRINT_RESULT(JOB_ERROR_NONE, nRet, "job_info_remove_trigger_event", JobGetError(nRet));
	}

	 return 0;
}

/** @} */
/** @} */
