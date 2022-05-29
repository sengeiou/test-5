//
// Copyright (c) 2021 Samsung Electronics Co., Ltd.
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
#include "ITs-capi-network-ua-common.h"

//& set: CapiNetwork-ua
ua_sensor_type_e g_eSensorType[] = {UA_SENSOR_BT,
			UA_SENSOR_BLE,
			UA_SENSOR_WIFI,
			UA_SENSOR_MOTION,
			UA_SENSOR_LIGHT,
			UA_SENSOR_AUDIO,
			//UA_SENSOR_MAX,
			UA_SENSOR_ALL
			};
int g_nEnumSize = sizeof(g_eSensorType) / sizeof(g_eSensorType[0]);

ua_detection_mode_e g_eDetectionMode[] = {UA_DETECT_MODE_ALL_SENSORS,
			UA_DETECT_MODE_ANY_SENSOR};
			/*UA_DETECT_MODE_INVALID*/

int g_nDetectModeEnumSize = sizeof(g_eDetectionMode) / sizeof(g_eDetectionMode[0]);

/** @addtogroup itc-capi-network-ua
*  @ingroup itc
*  @{
*/
/**
 * @function 		ITs_capi_network_ua_monitor_startup
 * @description	 	Called before each test
 * @parameter		NAUA_SENSOR_ALL
 * @return 			NA
 */
void ITs_capi_network_ua_monitor_startup(void)
{
	g_bUaInit = false;
	g_bIsUaFeatureSupported = false;
	g_bFeatureByPass = false;
	g_hMonitor = NULL;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	int nRet = UA_ERROR_NONE;

	g_bIsUaFeatureSupported = TCTCheckSystemInfoFeatureSupported(UA_FEATURE, API_NAMESPACE);

	nRet = ua_initialize();
	if(!g_bIsUaFeatureSupported)
	{
		if ( nRet != UA_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] ua_initialize failed to return UA_ERROR_NOT_SUPPORTED for unsupported feature, error returned = (%d)\\n", __FILE__, __LINE__,nRet);
			return;
		}

		FPRINTF("[%s:%d] ua_initialize is unsupported\\n", __FILE__, __LINE__);
		g_bFeatureByPass = true;
		return;
	}
	else if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_DONE)
	{
		FPRINTF("[%s:%d] ua_initialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		g_bUaInit = false;
		return;
	}

	nRet = ua_monitor_create(&g_hMonitor);
	if (nRet != UA_ERROR_NONE )
	{
		FPRINTF("[%s:%d] ua_monitor_create fail\\n", __FILE__, __LINE__);
		g_bUaInit = false;
		return;
	}
	if(g_hMonitor == NULL)
	{
		FPRINTF("[%s:%d] g_hMonitor handle is NULL\\n", __FILE__, __LINE__);
		g_bUaInit = false;
		return;
	}
	g_bUaInit = true;
}


/**
 * @function 		ITs_capi_network_ua_monitor_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_capi_network_ua_monitor_cleanup(void)
{
	int nRet = UA_ERROR_NONE;

	if (g_bIsUaFeatureSupported && g_bUaInit)
	{
		if(g_hMonitor)
		{
			nRet = ua_monitor_destroy(g_hMonitor);
			if ( nRet != UA_ERROR_NONE )
			{
				FPRINTF("[%s:%d] ua_monitor_destroy failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
			}
		}
		nRet = ua_deinitialize();
		if ( nRet != UA_ERROR_NONE )
		{
			FPRINTF("[%s:%d] ua_deinitialize failed, error returned =(%d)\\n", __FILE__, __LINE__, nRet);
		}
	}
	return;
}
/**
 * @function 		CapiNetworkUaMonitorSensorPresenceDetectedCallback
 * @description	 	Callback Function
 * @parameter		int result, ua_monitor_h monitor, ua_sensor_type_e sensor, ua_service_h service_handle, ua_device_h device_handle, ua_sensor_h sensor_handle, void *user_data
 * @return 			NA
 */
static void CapiNetworkUaMonitorSensorPresenceDetectedCallback(int result, ua_monitor_h monitor, ua_sensor_type_e sensor, ua_service_h service_handle, ua_device_h device_handle, ua_sensor_h sensor_handle, void *user_data)
{
	g_bCallBackHit = true;
}
/**
 * @function 		CapiNetworkUaMonitorSensorAbsenceDetectedCallback
 * @description	 	Callback Function
 * @parameter		int result, ua_monitor_h monitor, ua_service_h service_handle, ua_sensor_type_e sensor, ua_sensor_h sensor_handle, void *user_data
 * @return 			NA
 */
static void CapiNetworkUaMonitorSensorAbsenceDetectedCallback(int result, ua_monitor_h monitor, ua_service_h service_handle, ua_sensor_type_e sensor, ua_sensor_h sensor_handle, void *user_data)
{
	g_bCallBackHit = true;
}
/**
 * @function 		CapiNetworkUaMonitorSensorStatusChangedCallback
 * @description	 	Callback Function
 * @parameter		ua_monitor_h handle, ua_sensor_h sensor_handle, ua_sensor_type_e sensor_type, ua_sensor_report_e status, void *user_data
 * @return 			NA
 */
static void CapiNetworkUaMonitorSensorStatusChangedCallback(ua_monitor_h handle, ua_sensor_h sensor_handle, ua_sensor_type_e sensor_type, ua_sensor_report_e status, void *user_data)
{
	g_bCallBackHit = true;
}
/**
 * @function 		CapiNetworkUaMonitorScanCompletedCallback
 * @description	 	Callback Function
 * @parameter		ua_active_scan_type_e result, ua_monitor_h handle, ua_device_h device_handle, void *user_data
 * @return 			NA
 */
static void CapiNetworkUaMonitorScanCompletedCallback(ua_active_scan_type_e result, ua_monitor_h handle, ua_device_h device_handle, void *user_data)
{
	g_bCallBackHit = true;
}
/**
 * @function 		CapiNetworkUaMonitorForeachSensorCallBack
 * @description	 	Callback Function
 * @parameter		ua_service_h service_handle, void *user_data
 * @return 			bool
 */
static bool CapiNetworkUaMonitorForeachSensorCallBack(ua_sensor_type_e sensor, void *user_data)
{
	g_bCallBackHit = true;
	return true;
}
/**
 * @function 		CapiNetworkPresenceDetectionHelper
 * @description	 	Callback Function
 * @parameter		ua_service_h hService, ua_monitor_h hMonitor
 * @return 			int
 */
int CapiNetworkPresenceDetectionHelper(ua_monitor_h hMonitor, ua_service_h hService)
{
	bool bAvail;
	int nEnumCounter1;
	int nEnumCounter2;
	int nRet;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize; nEnumCounter1++)
	{
		bAvail = false;
		//precondition API
		nRet = ua_monitor_is_sensor_available(g_eSensorType[nEnumCounter1], &bAvail);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_is_sensor_available", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		if(bAvail == true)
		{
			nRet = ua_monitor_add_sensor(hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_add_sensor", UaGetError(nRet), ua_monitor_destroy(hMonitor));
			for ( nEnumCounter2 = 0; nEnumCounter2 < g_nDetectModeEnumSize; nEnumCounter2++)
			{
				//Target API
				nRet = ua_monitor_start_presence_detection(hMonitor, hService, g_eDetectionMode[nEnumCounter2], CapiNetworkUaMonitorSensorPresenceDetectedCallback, NULL);
				PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_start_presence_detection", UaGetError(nRet), ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]); ua_monitor_destroy(hMonitor));
				//Target API
				nRet = ua_monitor_stop_presence_detection(hMonitor);
				PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_stop_presence_detection", UaGetError(nRet), ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]); ua_monitor_destroy(hMonitor));
			}
			nRet = ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_remove_sensor", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		}
		else
			FPRINTF("[Line : %d][%s] sensor [%s] is not available\\n", __LINE__, API_NAMESPACE, UaGetEnumSensorString(g_eSensorType[nEnumCounter1]));
	}
	return 0;
}
/**
 * @function 		CapiNetworkAbsenceDetectionHelper
 * @description	 	Callback Function
 * @parameter		ua_service_h hService, ua_monitor_h hMonitor
 * @return 			int
 */
int CapiNetworkAbsenceDetectionHelper(ua_monitor_h hMonitor, ua_service_h hService)
{
	bool bAvail;
	int nEnumCounter1;
	int nEnumCounter2;
	int nRet;
	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize; nEnumCounter1++)
	{
		bAvail = false;
		//precondition API
		nRet = ua_monitor_is_sensor_available(g_eSensorType[nEnumCounter1], &bAvail);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_is_sensor_available", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService); ua_monitor_destroy(hMonitor));
		if(bAvail == true)
		{
			nRet = ua_monitor_add_sensor(hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_add_sensor", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService); ua_monitor_destroy(hMonitor));
			for ( nEnumCounter2 = 0; nEnumCounter2 < g_nDetectModeEnumSize; nEnumCounter2++)
			{
				//Target API
				nRet = ua_monitor_start_absence_detection(hMonitor, hService, g_eDetectionMode[nEnumCounter2], CapiNetworkUaMonitorSensorAbsenceDetectedCallback, NULL);
				PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_start_absence_detection", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService); ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]); ua_monitor_destroy(hMonitor));
				//Target API
				nRet = ua_monitor_stop_absence_detection(hMonitor);
				PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_stop_absence_detection", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService); ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]); ua_monitor_destroy(hMonitor));
			}
			nRet = ua_monitor_remove_sensor(hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_remove_sensor", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService); ua_monitor_destroy(hMonitor));
		}
		else
			FPRINTF("[Line : %d][%s] sensor [%s] is not available\\n", __LINE__, API_NAMESPACE, UaGetEnumSensorString(g_eSensorType[nEnumCounter1]));
	}
	return 0;
}

//& purpose: Creates and destroys the ua monitor's handle
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_create_destroy_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates and destroys the ua monitor's handle.
* @scenario				Creates and destroys the ua monitor's handle.
* @apicovered			ua_monitor_create, ua_monitor_destroy
* @passcase				If ua_monitor_create, ua_monitor_destroy is successfull
* @failcase 			If ua_monitor_create, ua_monitor_destroy fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_create_destroy_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;

	//Target API
	nRet = ua_monitor_destroy(g_hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet));

	//Target API
	nRet = ua_monitor_create(&g_hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_create", UaGetError(nRet));
	CHECK_HANDLE(g_hMonitor, "ua_monitor_create");

	return 0;
}
//& purpose: Adds and removes sensors to UA monitor for which monitoring is to be done..
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_add_remove_sensor_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Adds and removes sensors to UA monitor for which monitoring is to be done.
* @scenario				Adds and removes sensors to UA monitor for which monitoring is to be done.
* @apicovered			ua_monitor_add_sensor, ua_monitor_remove_sensor
* @passcase				If ua_monitor_add_sensor, ua_monitor_remove_sensor is successfull
* @failcase 			If ua_monitor_add_sensor, ua_monitor_remove_sensor fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_add_remove_sensor_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	bool bAvail = false;
	int nEnumCounter1 = 0;

	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize; nEnumCounter1++)
	{
		bAvail = false;
		//precondition API
		nRet = ua_monitor_is_sensor_available(g_eSensorType[nEnumCounter1], &bAvail);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_is_sensor_available", UaGetError(nRet));
		if(bAvail == true)
		{
			//Target API
			nRet = ua_monitor_add_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_add_sensor", UaGetError(nRet));
			//Target API
			nRet = ua_monitor_remove_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_remove_sensor", UaGetError(nRet));
		}
		else
			FPRINTF("[Line : %d][%s] sensor [%s] is not available\\n", __LINE__, API_NAMESPACE, UaGetEnumSensorString(g_eSensorType[nEnumCounter1]));
	}

	return 0;
}
//& purpose: Retrieves all sensors present in UA monitor.
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_foreach_sensor_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Retrieves all sensors present in UA monitor.
* @scenario				Retrieves all sensors present in UA monitor.
* @apicovered			ua_monitor_foreach_sensor
* @passcase				If ua_monitor_foreach_sensor is successfull
* @failcase 			If ua_monitor_foreach_sensor fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_foreach_sensor_p(void)
{
	START_TEST;

	g_bCallBackHit = false;
	int nRet = UA_ERROR_NONE;
	ua_monitor_h hMonitor = NULL;
	bool bAvail = false;
	int nEnumCounter1 = 0;

	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize; nEnumCounter1++)
	{
		bAvail = false;
		//precondition API
		nRet = ua_monitor_is_sensor_available(g_eSensorType[nEnumCounter1], &bAvail);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_is_sensor_available", UaGetError(nRet));
		if(bAvail == true)
		{
			nRet = ua_monitor_add_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_add_sensor", UaGetError(nRet));
			//Target API
			nRet = ua_monitor_foreach_sensor(g_hMonitor, CapiNetworkUaMonitorForeachSensorCallBack, NULL);
			PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_foreach_sensor", UaGetError(nRet), ua_monitor_remove_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]));
			PRINT_RESULT_CLEANUP(true, g_bCallBackHit, "ua_monitor_foreach_sensor", "CallBack Not Invoked", ua_monitor_remove_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]));

			nRet = ua_monitor_remove_sensor(g_hMonitor, g_eSensorType[nEnumCounter1]);
			PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_remove_sensor", UaGetError(nRet));
		}
		else
			FPRINTF("[Line : %d][%s] sensor is not available\\n", __LINE__, API_NAMESPACE);
	}

	return 0;
}
//& purpose: Checks if sensor is available or not
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_is_sensor_available_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Checks if sensor is available or not.
* @scenario				Checks if sensor is available or not.
* @apicovered			ua_monitor_is_sensor_available
* @passcase				If ua_monitor_is_sensor_available is successfull
* @failcase 			If ua_monitor_is_sensor_available fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_is_sensor_available_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	bool bAvail = false;
	int nEnumCounter1 = 0;

	for ( nEnumCounter1 = 0; nEnumCounter1 < g_nEnumSize; nEnumCounter1++)
	{
		bAvail = false;
		//Target API
		nRet = ua_monitor_is_sensor_available(g_eSensorType[nEnumCounter1], &bAvail);
		PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_is_sensor_available", UaGetError(nRet));
		if(bAvail == true)
		{
			FPRINTF("[Line : %d][%s] [%s]sensor is available\\n", __LINE__, API_NAMESPACE, UaGetEnumSensorString(g_eSensorType[nEnumCounter1]));
		}
		else
			FPRINTF("[Line : %d][%s] sensor [%s] is not available\\n", __LINE__, API_NAMESPACE, UaGetEnumSensorString(g_eSensorType[nEnumCounter1]));
	}

	return 0;
}
//& purpose: Sets and unsets sensor status changed callback
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_set_unset_sensor_status_changed_cb_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets and unsets sensor status changed callback. Callback to be invoked
						when sensor status changes from 'PRESENCE' to 'ABSENCE' or vice-versa.
* @scenario				Sets and unsets sensor status changed callback. Callback to be invoked
						when sensor status changes from 'PRESENCE' to 'ABSENCE' or vice-versa.
* @apicovered			ua_monitor_set_sensor_status_changed_cb, ua_monitor_unset_sensor_status_changed_cb
* @passcase				If ua_monitor_set_sensor_status_changed_cb, ua_monitor_unset_sensor_status_changed_cb is successfull
* @failcase 			If ua_monitor_set_sensor_status_changed_cb, ua_monitor_unset_sensor_status_changed_cb fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_set_unset_sensor_status_changed_cb_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_monitor_h hMonitor = NULL;

	//Target API
	nRet = ua_monitor_set_sensor_status_changed_cb(g_hMonitor, CapiNetworkUaMonitorSensorStatusChangedCallback, NULL);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_set_sensor_status_changed_cb", UaGetError(nRet));
	//Target API
	nRet = ua_monitor_unset_sensor_status_changed_cb(g_hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_unset_sensor_status_changed_cb", UaGetError(nRet));

	return 0;
}
//& purpose: Starts and stops user presence detection
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_start_stop_presence_detection_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Starts and stops user presence detection.
* @scenario				Starts and stops user presence detection.
* @apicovered			ua_monitor_start_presence_detection, ua_monitor_stop_presence_detection
* @passcase				If ua_monitor_start_presence_detection, ua_monitor_stop_presence_detection is successfull
* @failcase 			If ua_monitor_start_presence_detection, ua_monitor_stop_presence_detection fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_start_stop_presence_detection_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_service_h hService = NULL;
	ua_monitor_h hMonitor = NULL;

	nRet = ua_monitor_create(&hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_create", UaGetError(nRet));
	CHECK_HANDLE(hMonitor, "ua_monitor_create");

	nRet = ua_get_default_service(&hService);
	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		CHECK_HANDLE_CLEANUP(hService, "ua_service_create", ua_monitor_destroy(hMonitor));

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			ua_monitor_destroy(hMonitor);
			return 1;
		}
		nRet = CapiNetworkPresenceDetectionHelper(hMonitor, hService);
		if(nRet == 1)
		{
			ua_service_remove(hService);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_monitor_destroy(hMonitor);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}

		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		CHECK_HANDLE_CLEANUP(hService, "ua_get_default_service", ua_monitor_destroy(hMonitor));
		nRet = CapiNetworkPresenceDetectionHelper(hMonitor, hService);
		if(nRet == 1)
		{
			return 1;
		}
		nRet = ua_monitor_destroy(hMonitor);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet));
	}
	return 0;
}
//& purpose: Starts and stops user absence detection
//& type: auto
/**
* @testcase 			ITc_capi_network_ua_monitor_start_stop_absence_detection_p
* @since_tizen 			6.5
* @author				SRID(manu.tiwari)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Starts and stops user absence detection.
* @scenario				Starts and stops user absence detection.
* @apicovered			ua_monitor_start_absence_detection, ua_monitor_stop_absence_detection
* @passcase				If ua_monitor_start_absence_detection, ua_monitor_stop_absence_detection is successfull
* @failcase 			If ua_monitor_start_absence_detection, ua_monitor_stop_absence_detection fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_capi_network_ua_monitor_start_stop_absence_detection_p(void)
{
	START_TEST;

	int nRet = UA_ERROR_NONE;
	ua_service_h hService = NULL;
	ua_monitor_h hMonitor = NULL;
	bool bAvail = false;
	int nEnumCounter1 = 0;

	nRet = ua_monitor_create(&hMonitor);
	PRINT_RESULT(UA_ERROR_NONE, nRet, "ua_monitor_create", UaGetError(nRet));
	CHECK_HANDLE(hMonitor, "ua_monitor_create");

	nRet = ua_get_default_service(&hService);
	if (nRet != UA_ERROR_NONE)
	{
		nRet = ua_service_create(g_hServiceStr, &hService);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_service_create", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		CHECK_HANDLE_CLEANUP(hService, "ua_service_create", ua_monitor_destroy(hMonitor));

		nRet = ua_service_add(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_ALREADY_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_add", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			ua_monitor_destroy(hMonitor);
			return 1;
		}
		nRet = CapiNetworkAbsenceDetectionHelper(hMonitor, hService);
		if(nRet == 1)
		{
			ua_service_remove(hService);
			ua_service_destroy(hService);
			return 1;
		}
		nRet = ua_monitor_destroy(hMonitor);
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet), ua_service_remove(hService); ua_service_destroy(hService));

		nRet = ua_service_remove(hService);
		if (nRet != UA_ERROR_NONE && nRet != UA_ERROR_NOT_REGISTERED)
		{
			FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, "ua_service_remove", UaGetError(nRet), nRet);
			ua_service_destroy(hService);
			return 1;
		}

		nRet = ua_service_destroy(hService);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_service_destroy", UaGetError(nRet));
	}
	else
	{
		PRINT_RESULT_CLEANUP(UA_ERROR_NONE, nRet, "ua_get_default_service", UaGetError(nRet), ua_monitor_destroy(hMonitor));
		CHECK_HANDLE_CLEANUP(hService, "ua_get_default_service", ua_monitor_destroy(hMonitor));
		nRet = CapiNetworkAbsenceDetectionHelper(hMonitor, hService);
		if(nRet == 1)
		{
			return 1;
		}
		nRet = ua_monitor_destroy(hMonitor);
		PRINT_RESULT_NORETURN(UA_ERROR_NONE, nRet, "ua_monitor_destroy", UaGetError(nRet));
	}
	return 0;
}
