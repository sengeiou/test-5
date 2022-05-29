/*
 * Copyright (c) 2019 Samsung Electronics Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License")
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "ITs-battery-monitor-common.h"

/** @addtogroup battery-monitor
*  @ingroup itc
*  @{
*/

//& set: Battery-Monitor
/**
* @function		ITs_battery_monitor_startup
* @description		Called before each test, checks for battery feature
* @parameter		NA
* @return		NA
*/
void ITs_battery_monitor_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_battery_monitor_startup\\n", __LINE__, API_NAMESPACE, API_NAMESPACE);
#endif
	g_bBatteryFeatureNotSupported = false;

	bool bFeatureStatus = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	if(!bFeatureStatus)
	{
		g_bBatteryFeatureNotSupported = true;
	}
	return;
}

/**
 * @function		ITs_battery_monitor_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void ITs_battery_monitor_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_battery_monitor_cleanup\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

//& type : auto
//& purpose: Creates and Destroy a handle to the Battery Consumption for getting resource based usage.
/**
* @testcase			ITc_battery_monitor_battery_usage_data_destroy_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Creates and Destroy a handle to the Battery Consumption for getting resource based usage.
* @scenario			Create battery monitor handle and destroy created handle\n
*				and check for Pass/Fail.
* @apicovered			battery_monitor_create, battery_monitor_battery_usage_data_destroy
* @passcase			battery_monitor_create, battery_monitor_battery_usage_data_destroy are successful and return correct value
* @failcase			battery_monitor_create, battery_monitor_battery_usage_data_destroy gets failed or return null value
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_battery_monitor_battery_usage_data_destroy_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
        battery_usage_data_h hBatteryMonitorAPP = NULL;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }
        nRet = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, start_time, end_time, &hBatteryMonitorAPP);
        if ( g_bBatteryFeatureNotSupported )
        {
                PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
                return 0;
        }
        if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
        {
                FPRINTF("[Line : %d][%s] record is not found\\n", __LINE__, API_NAMESPACE);
                return 0;
        }


	PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
	CHECK_HANDLE(hBatteryMonitorAPP, "battery_monitor_get_power_usage_by_app_for_all_resources");

	nRet = battery_monitor_battery_usage_data_destroy(hBatteryMonitorAPP);
	PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_battery_usage_data_destroy", BatteryMonitorGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the battery-percent for specific resource from available data.
/**
* @testcase                     ITc_battery_monitor_usage_data_get_power_usage_per_resource_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the battery-percent for specific resource from available data.
* @scenario			Create battery monitor handle\n
*				get battery percent using this handle and check for Pass/Fail.
* @apicovered			battery_monitor_create, battery_monitor_usage_data_get_power_usage_per_resource, battery_monitor_battery_usage_data_destroy
* @passcase			battery_monitor_create, battery_monitor_usage_data_get_power_usage_per_resource are successful and return correct value
* @failcase			battery_monitor_create, battery_monitor_usage_data_get_power_usage_per_resource gets failed or return null value
* @precondition			N/A
* @postcondition		Destroy battery monitor handle.
*/
int ITc_battery_monitor_usage_data_get_power_usage_per_resource_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
	double nBatteryUsage = 0.0;
	battery_usage_data_h hBatteryMonitorAPP = NULL;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }


	battery_monitor_resource_id_e eResourceID[] = {
		BATTERY_MONITOR_RESOURCE_ID_BLE,
		BATTERY_MONITOR_RESOURCE_ID_WIFI,
		BATTERY_MONITOR_RESOURCE_ID_CPU,
		BATTERY_MONITOR_RESOURCE_ID_DISPLAY,
		BATTERY_MONITOR_RESOURCE_ID_DEVICE_NETWORK,
		BATTERY_MONITOR_RESOURCE_ID_GPS_SENSOR,
	};

        nRet = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, start_time, end_time, &hBatteryMonitorAPP);
        if ( g_bBatteryFeatureNotSupported )
        {
                PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
                return 0;
        }

        if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
        {
                FPRINTF("[Line : %d][%s] record is not found\\n", __LINE__, API_NAMESPACE);
                return 0;
        }
        PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
        CHECK_HANDLE(hBatteryMonitorAPP, "battery_monitor_get_power_usage_by_app_for_all_resources");
	int nEnumSize = sizeof(eResourceID) / sizeof(eResourceID[0]);
	int nEnumCounter;

	for(nEnumCounter = 0; nEnumCounter < nEnumSize; nEnumCounter++)
	{
		//Targer API
		nRet = battery_monitor_usage_data_get_power_usage_per_resource(hBatteryMonitorAPP, eResourceID[nEnumCounter], &nBatteryUsage);
		if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
	         {
	                 FPRINTF("[Line : %d][%s] record is not found for resource ID[%d]\\n", __LINE__, API_NAMESPACE, eResourceID[nEnumCounter]);
	         }
		else
		{
			PRINT_RESULT_CLEANUP(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_usage_data_get_power_usage_per_resource", BatteryMonitorGetError(nRet), battery_monitor_battery_usage_data_destroy(hBatteryMonitorAPP));
			FPRINTF("[Line : %d][%s] battery_monitor_usage_data_get_power_usage_per_resource returned battary usage[%f] for resource ID [%d] \\n", __LINE__, API_NAMESPACE, nBatteryUsage, eResourceID[nEnumCounter]);
		}
	}

        nRet = battery_monitor_battery_usage_data_destroy(hBatteryMonitorAPP);
        PRINT_RESULT_NORETURN(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_battery_usage_data_destroy", BatteryMonitorGetError(nRet));

	return 0;
}

//& type : auto
//& purpose: Gets the battery_data_usage_h with battery consumption by the specified application.
/**
* @testcase			ITc_battery_monitor_get_power_usage_by_app_for_all_resources_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the battery_data_usage_h with battery consumption by the specified application.
* @scenario			Gets the battery monitor handle and call battery_monitor_usage_data_get_power_usage_per_resource\n
*				battery consumption by the specified application and check for Pass/Fail.
* @apicovered			battery_monitor_get_power_usage_by_app_for_all_resources, battery_monitor_battery_usage_data_destroy
* @passcase			battery_monitor_get_power_usage_by_app_for_all_resources is successful and return correct value
* @failcase			battery_monitor_get_power_usage_by_app_for_all_resources gets failed or return null value
* @precondition			N/A
* @postcondition		Destroy gathered battery monitor handle.
*/
int ITc_battery_monitor_get_power_usage_by_app_for_all_resources_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
	double nBatteryUsage = 0.0;
	battery_usage_data_h hBatteryMonitorAPP = NULL;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }



	battery_monitor_resource_id_e eResourceID[] = {
		BATTERY_MONITOR_RESOURCE_ID_BLE,
		BATTERY_MONITOR_RESOURCE_ID_WIFI,
		BATTERY_MONITOR_RESOURCE_ID_CPU,
		BATTERY_MONITOR_RESOURCE_ID_DISPLAY,
		BATTERY_MONITOR_RESOURCE_ID_DEVICE_NETWORK,
		BATTERY_MONITOR_RESOURCE_ID_GPS_SENSOR,
	};


	int nIDEnumSize = sizeof(eResourceID) / sizeof(eResourceID[0]);
	int nIDEnumCounter;

        //Targer API
	nRet = battery_monitor_get_power_usage_by_app_for_all_resources(TEST_APP_ID, start_time, end_time, &hBatteryMonitorAPP);
	if ( g_bBatteryFeatureNotSupported )
	{
		PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
		return 0;
	}
        if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
        {
                FPRINTF("[Line : %d][%s] record not found\\n", __LINE__, API_NAMESPACE);
                return 0;
        }
	PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_app_for_all_resources", BatteryMonitorGetError(nRet));
	CHECK_HANDLE(hBatteryMonitorAPP, "battery_monitor_get_power_usage_by_app_for_all_resources");

	for(nIDEnumCounter = 0; nIDEnumCounter < nIDEnumSize; nIDEnumCounter++)
	{
		nRet = battery_monitor_usage_data_get_power_usage_per_resource(hBatteryMonitorAPP, eResourceID[nIDEnumCounter], &nBatteryUsage);
		if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
	        {
	                 FPRINTF("[Line : %d][%s] record is not found for resource ID[%d]\\n", __LINE__, API_NAMESPACE,eResourceID[nIDEnumCounter]);
	        }
		else
		{
			PRINT_RESULT_CLEANUP(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_usage_data_get_power_usage_per_resource", BatteryMonitorGetError(nRet), battery_monitor_battery_usage_data_destroy(hBatteryMonitorAPP));
			FPRINTF("[Line : %d][%s] battery_monitor_usage_data_get_power_usage_per_resource returned battary usage[%f] for resource ID [%d] \\n", __LINE__, API_NAMESPACE, nBatteryUsage, eResourceID[nIDEnumCounter]);
		}
	}
	nRet = battery_monitor_battery_usage_data_destroy(hBatteryMonitorAPP);
	PRINT_RESULT_NORETURN(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_battery_usage_data_destroy", BatteryMonitorGetError(nRet));
	hBatteryMonitorAPP = NULL;


	return 0;
}

//& type : auto
//& purpose: Gets the battery consumption for the specific resource for the given application.
/**
* @testcase			ITc_battery_monitor_get_power_usage_by_app_per_resource_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the battery consumption for the specific resource for the given application.
* @scenario			Get battery usage using different recource id for different duration\n
*				check for Pass/Fail.
* @apicovered			battery_monitor_get_power_usage_by_app_per_resource
* @passcase			battery_monitor_get_power_usage_by_app_per_resource is successful and return correct value
* @failcase			battery_monitor_get_power_usage_by_app_per_resource gets failed or return null value
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_battery_monitor_get_power_usage_by_app_per_resource_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
	double nBatteryUsage = 0.0;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }


	battery_monitor_resource_id_e eResourceID[] = {
		BATTERY_MONITOR_RESOURCE_ID_BLE,
		BATTERY_MONITOR_RESOURCE_ID_WIFI,
		BATTERY_MONITOR_RESOURCE_ID_CPU,
		BATTERY_MONITOR_RESOURCE_ID_DISPLAY,
		BATTERY_MONITOR_RESOURCE_ID_DEVICE_NETWORK,
		BATTERY_MONITOR_RESOURCE_ID_GPS_SENSOR,
	};

	int nIDEnumSize = sizeof(eResourceID) / sizeof(eResourceID[0]);
	int nIDEnumCounter;

	for(nIDEnumCounter = 0; nIDEnumCounter < nIDEnumSize; nIDEnumCounter++)
	{
                //Targer API
		nRet = battery_monitor_get_power_usage_by_app_per_resource(TEST_APP_ID, eResourceID[nIDEnumCounter], start_time, end_time, &nBatteryUsage);
		if ( g_bBatteryFeatureNotSupported )
		{
			PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_app_per_resource", BatteryMonitorGetError(nRet));
			return 0;
		}
                if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
                {
                        FPRINTF("[Line : %d][%s] record is not found\\n", __LINE__, API_NAMESPACE);
                        return 0;
                }
		PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_app_per_resource", BatteryMonitorGetError(nRet));
		FPRINTF("[Line : %d][%s] battery_monitor_get_power_usage_by_app_per_resource returned battary usage[%f] resource ID [%d] \\n", __LINE__, API_NAMESPACE, nBatteryUsage, eResourceID[nIDEnumCounter]);

	}

	return 0;
}

//& type : auto
//& purpose: Gets the total battery usage in percent by an application for certain time duration
/**
* @testcase			ITc_battery_monitor_get_power_usage_by_app_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto
* @description			Gets the total battery usage in percent by an application for certain time duration.
* @scenario			Use test app id and different duration to get battery usage\n
*				check for Pass/Fail.
* @apicovered			battery_monitor_get_power_usage_by_app
* @passcase			battery_monitor_get_power_usage_by_app is successful and return correct value
* @failcase			battery_monitor_get_power_usage_by_app gets failed or return null value
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_battery_monitor_get_power_usage_by_app_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
	double nBatteryUsage = 0.0;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }


	//Targer API
	nRet = battery_monitor_get_power_usage_by_app(TEST_APP_ID, start_time, end_time, &nBatteryUsage);
        if ( g_bBatteryFeatureNotSupported )
	{
		PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_app", BatteryMonitorGetError(nRet));
		return 0;
	}
        if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
        {
                FPRINTF("[Line : %d][%s] record not found\\n", __LINE__, API_NAMESPACE);
                return 0;
        }
	PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_app", BatteryMonitorGetError(nRet));
        FPRINTF("[Line : %d][%s] battery_monitor_get_power_usage_by_app returned battary usage[%f] \\n", __LINE__, API_NAMESPACE, nBatteryUsage);

        return 0;
}

//& type : auto
//& purpose: Gets the battery-percent usage by a resource for certain time duration.
/**
* @testcase			ITc_battery_monitor_get_power_usage_by_resource_p
* @since_tizen			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type				auto

* @description			Gets the battery-percent usage by a resource for certain time duration.
* @scenario			Based on different resource ID get battery usage for different duration\n
*				check for Pass/Fail.
* @apicovered			battery_monitor_get_power_usage_by_resource
* @passcase			battery_monitor_get_power_usage_by_resource is successful and return correct value
* @failcase			battery_monitor_get_power_usage_by_resource gets failed or return null value
* @precondition			N/A
* @postcondition		N/A
*/
int ITc_battery_monitor_get_power_usage_by_resource_p(void)
{
	START_TEST_NO_CHECK;

	int nRet = -1;
	double nBatteryUsage = 0.0;
        time_t start_time;
        time_t end_time;
        nRet = BatteryMonitorGetTime(&start_time, &end_time);
        if(nRet == 1)
        {
                FPRINTF("[Line : %d][%s] error returned = failed precondition, time\\n", __LINE__, API_NAMESPACE);
                return 1;
        }

	battery_monitor_resource_id_e eResourceID[] = {
		BATTERY_MONITOR_RESOURCE_ID_BLE,
		BATTERY_MONITOR_RESOURCE_ID_WIFI,
		BATTERY_MONITOR_RESOURCE_ID_CPU,
		BATTERY_MONITOR_RESOURCE_ID_DISPLAY,
		BATTERY_MONITOR_RESOURCE_ID_DEVICE_NETWORK,
		BATTERY_MONITOR_RESOURCE_ID_GPS_SENSOR,
	};

	int nIDEnumSize = sizeof(eResourceID) / sizeof(eResourceID[0]);
	int nIDEnumCounter;

	for(nIDEnumCounter = 0; nIDEnumCounter < nIDEnumSize; nIDEnumCounter++)
	{
	        nRet = battery_monitor_get_power_usage_by_resource(eResourceID[nIDEnumCounter], start_time, end_time, &nBatteryUsage);
		if ( g_bBatteryFeatureNotSupported )
		{
			PRINT_RESULT(BATTERY_MONITOR_ERROR_NOT_SUPPORTED, nRet, "battery_monitor_get_power_usage_by_resource", BatteryMonitorGetError(nRet));
			return 0;
		}
                if(nRet == BATTERY_MONITOR_ERROR_RECORD_NOT_FOUND)
                {
                        FPRINTF("[Line : %d][%s] record not found\\n", __LINE__, API_NAMESPACE);
                        return 0;
                }
		PRINT_RESULT(BATTERY_MONITOR_ERROR_NONE, nRet, "battery_monitor_get_power_usage_by_resource", BatteryMonitorGetError(nRet));
		FPRINTF("[Line : %d][%s] battery_monitor_get_power_usage_by_resource returned battary usage[%f] for resource ID [%d] \\n", __LINE__, API_NAMESPACE, nBatteryUsage, eResourceID[nIDEnumCounter]);
	}

	return 0;
}

/** @} */
/** @} */
