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
#include "ITs-wifi-manager-common.h"

//& set: WifiManager

/** @addtogroup itc-wifi-manager
*  @ingroup itc
*  @{
*/

/**
 * @function 		ITs_wifi_manager_startup
 * @description	 	Called before each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	g_bIsFeatureMismatched = false;
	g_bWifiManagerCreation = false;
	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(FEATURE_WIFI, API_NAMESPACE);

	int nRet = wifi_manager_initialize(&g_hWifi);
	if ( !g_bFeatureWifi)
	{
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize failed to return TIZEN_ERROR_NOT_SUPPORTED for unsupported feature, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
			g_bIsFeatureMismatched = true;
			return;
		}

		FPRINTF("[%s:%d] wifi_manager_initialize is unsupported\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize is unsupported", __FILE__, __LINE__);
		g_bIsFeatureMismatched = false;
	}
	else if ( nRet != WIFI_MANAGER_ERROR_NONE )
	{
		FPRINTF("[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)\\n", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_initialize failed, error returned = %s (%d)", __FILE__, __LINE__, WifiManagerGetError(nRet), nRet);
		g_bWifiManagerCreation = false;
	}
	else
	{
		g_bWifiManagerCreation = true;
	}
	return;
}


/**
 * @function 		ITs_wifi_manager_cleanup
 * @description	 	Called after each test
 * @parameter		NA
 * @return 			NA
 */
void ITs_wifi_manager_cleanup(void)
{
	int nRet = 0;

	if (g_hWifi) {
		nRet = wifi_manager_deinitialize(g_hWifi);
		if(nRet !=0)
		{
			FPRINTF("wifi_manager_deinitialize failed\\n");
			dlog_print(DLOG_ERROR, "NativeTCT", "wifi_manager_deinitialize failed");
		}
		g_hWifi = NULL;
	}

	return;
}
#define SET_FREQ 2412
//& purpose: Get all the Access Points found during scan.
//& type: auto
/**
* @testcase				ITc_wifi_manager_foreach_found_ap_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Get all the Access Points found during scan.
* @apicovered			wifi_manager_foreach_found_ap, wifi_manager_pre_connect
* @passcase				When  wifi_manager_foreach_found_ap, wifi_manager_pre_connect API returns 0
* @failcase				If  wifi_manager_foreach_found_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_foreach_found_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_pre_activate", WifiManagerGetError(nRet));

	g_bWifiManagerCB = false;
	nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scan", WifiManagerGetError(nRet))

	RUN_POLLING_LOOP;

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scan not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scan not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;

	nRet = wifi_manager_foreach_found_ap(g_hWifi, wifi_manager_foreach_found_ap_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_foreach_found_ap", WifiManagerGetError(nRet));

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_foreach_found_ap_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_foreach_found_ap_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}




//& purpose: Initializes/deinitialize Wi-Fi
//& type: auto
/**
* @testcase				ITc_wifi_manager_initialize_deinitialize_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Initializes/deinitialize Wi-Fi
* @apicovered			 wifi_manager_initialize, wifi_manager_deinitialize
* @passcase				When  wifi_manager_initialize, wifi_manager_deinitialize API returns 0
* @failcase				If  wifi_manager_initialize, wifi_manager_deinitialize returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_initialize_deinitialize_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = wifi_manager_deinitialize(g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deinitialize", WifiManagerGetError(nRet));
	g_hWifi = NULL;

	nRet =  wifi_manager_initialize(&g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_initialize", WifiManagerGetError(nRet));

	nRet = wifi_manager_deinitialize(g_hWifi);
	PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deinitialize", WifiManagerGetError(nRet));
	g_hWifi = NULL;

	return 0;
}


//& purpose: Activate and Deactivate Wi-Fi
//& type: auto
/**
* @testcase				ITc_wifi_manager_activate_deactivate_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Activate and Deactivate Wi-Fi
* @apicovered			wifi_manager_activate, wifi_manager_is_activated, wifi_manager_deactivate
* @passcase				When  wifi_manager_activate, wifi_manager_is_activated, wifi_manager_deactivate API returns 0
* @failcase				If  wifi_manager_activate, wifi_manager_is_activated, wifi_manager_deactivate returns non zero value
* @precondition			wifi manager must be initialize
* @postcondition		NA
*/
int ITc_wifi_manager_activate_deactivate_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	g_bWifiManagerCB = false;
	bool bActivated = false;
	nTimeoutId = 0;

	//Target API
	int nRet =  wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_is_activated", WifiManagerGetError(nRet));
	if(bActivated == false)
	{
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCB )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
			return 1;
		}
	}
	g_bWifiManagerCB = false;
	//Target API
	nRet = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deactivate", WifiManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_deactivated_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_deactivated_callback not invoked!!", __FILE__, __LINE__);
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
		}
		return 1;
	}

	nTimeoutId = 0;
	g_bWifiManagerCB = false;

	//Target API
	nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
	RUN_POLLING_LOOP;

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_activated_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activated_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Disconnect Wi-Fi and ensure the picker tested callback is triggered.
//& type: auto
/**
* @testcase				ITc_wifi_manager_activate_with_wifi_picker_tested_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Disconnect Wi-Fi and ensure the picker tested callback is triggered.
* @apicovered			wifi_manager_activate_with_wifi_picker_tested
* @passcase				When  wifi_manager_activate_with_wifi_picker_tested API returns 0
* @failcase				If  wifi_manager_activate_with_wifi_picker_tested returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_activate_with_wifi_picker_tested_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	bool bActivated = false;

	int nRet = wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_is_activated", WifiManagerGetError(nRet));

	if(bActivated)
	{
		FPRINTF("[%s:%d] wifi is activated!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi is activated!!", __FILE__, __LINE__);
		nRet = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deactivate", WifiManagerGetError(nRet));
		RUN_POLLING_LOOP;
		if( !g_bWifiManagerCB )
		{
			FPRINTF("[%s:%d] wifi_manager_deactivated_callback not invoked!!\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_deactivated_callback not invoked!!", __FILE__, __LINE__);
			return 1;
		}
	}

	g_bWifiManagerCB = false;
	nTimeoutId = 0;
	nRet =  wifi_manager_activate_with_wifi_picker_tested(g_hWifi, wifi_manager_activated_callback, NULL);
	//PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_activate_with_wifi_picker_tested", WifiManagerGetError(nRet),wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL));
	if(nRet != WIFI_MANAGER_ERROR_NONE)
	{

		FPRINTF("[%s:%d] wifi_manager_activate_with_wifi_picker_tested error =%s!!\\n", __FILE__, __LINE__,WifiManagerGetError(nRet));
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activate_with_wifi_picker_tested error =%s!!", __FILE__, __LINE__,WifiManagerGetError(nRet));
		int nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		if(nRet != WIFI_MANAGER_ERROR_NONE)
		{
			FPRINTF("[%s:%d] wifi_manager_activate_with_wifi_picker_tested error =%s!!\\n", __FILE__, __LINE__,WifiManagerGetError(nRet));
			dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activate_with_wifi_picker_tested error =%s!!", __FILE__, __LINE__,WifiManagerGetError(nRet));
			return 1;
		}

		RUN_POLLING_LOOP;
		return 1;

	}
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_activated_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activated_callback not invoked!!", __FILE__, __LINE__);
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
		}
		return 1;
	}

	return 0;
}

//& purpose: Get Wi-Fi connection state.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_connection_state_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Get Wi-Fi connection state.
* @apicovered			wifi_manager_get_connection_state
* @passcase				When  wifi_manager_get_connection_state API returns 0
* @failcase				If  wifi_manager_get_connection_state returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_connection_state_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_connection_state_e eConnState = -1;

	int nRet =  wifi_manager_get_connection_state(g_hWifi, &eConnState);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_connection_state", WifiManagerGetError(nRet));

	if(eConnState == -1)
	{
		FPRINTF("[%s:%d] wifi_manager_get_connection_state returned value is not correct!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_get_connection_state returned value is not correct!!", __FILE__, __LINE__);
		return 1;
	}
	return 0;
}

//& purpose: Get Wi-Fi connection state.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_mac_address_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Get Wi-Fi connection state.
* @apicovered			wifi_manager_get_mac_address
* @passcase				When  wifi_manager_get_mac_address API returns 0
* @failcase				If  wifi_manager_get_mac_address returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_mac_address_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *pMacAddress = NULL;

	int nRet =  wifi_manager_get_mac_address(g_hWifi, &pMacAddress);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_mac_address", WifiManagerGetError(nRet));

	if(pMacAddress == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_get_mac_address returned value is not correct!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "[%s:%d] wifi_manager_get_mac_address returned value is not correct!!", __FILE__, __LINE__);
		return 1;
	}

	FREE_MEMORY(pMacAddress);

	return 0;
}



//& purpose: Scan for specific ESSID. When AP is found the callback is triggered.
//& type: auto
/**
* @testcase				ITc_wifi_manager_scan_specific_ap_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Scan for specific ESSID. When AP is found the callback is triggered.
* @apicovered			wifi_manager_scan_specific_ap
* @passcase				When  wifi_manager_scan_specific_ap API returns 0
* @failcase				If  wifi_manager_scan_specific_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_scan_specific_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char ap_name[CONFIG_VALUE_LEN_MAX];
	nTimeoutId = 0;
	g_bWifiManagerCB = false;

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s\\n", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

	//Target API
	int nRet =  wifi_manager_scan_specific_ap(g_hWifi, ap_name, wifi_manager_scanned_specific_ap_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scan_specific_ap", WifiManagerGetError(nRet));
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scanned_specific_ap_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scanned_specific_ap_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Scan for specific ESSID. When AP is found the callback is triggered.
//& type: auto
/**
* @testcase				ITc_wifi_manager_foreach_found_specific_ap_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Scan for Specitic ESSID. When AP is found, callback is triggered.
* @apicovered			wifi_manager_foreach_found_specific_ap
* @passcase				When  wifi_manager_foreach_found_specific_ap API returns 0
* @failcase				If  wifi_manager_foreach_found_specific_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_foreach_found_specific_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	char ap_name[CONFIG_VALUE_LEN_MAX];

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_pre_activate", WifiManagerGetError(nRet));

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s\\n", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;
	nRet = wifi_manager_scan_specific_ap(g_hWifi, ap_name, wifi_manager_scanned_specific_ap_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scan_specific_ap", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scanned_specific_ap_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scanned_specific_ap_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;

	nRet =  wifi_manager_foreach_found_specific_ap(g_hWifi, wifi_manager_foreach_found_specific_ap_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_foreach_found_specific_ap", WifiManagerGetError(nRet));

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_foreach_found_ap_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_foreach_found_ap_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Registers the callback called when the device state is changed.
//& type: auto
/**
* @testcase				ITc_wifi_manager_set_unset_device_state_changed_cb_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Registers the callback called when the device state is changed.
* @apicovered			wifi_manager_set_device_state_changed_cb, wifi_manager_unset_device_state_changed_cb
* @passcase				When  wifi_manager_set_device_state_changed_cb, wifi_manager_unset_device_state_changed_cb API returns 0
* @failcase				If  wifi_manager_set_device_state_changed_cb, wifi_manager_unset_device_state_changed_cb returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_set_unset_device_state_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	bool bActivated = false;
	g_bWifiManagerCBHit = false;

	//Target API
	int nRet = wifi_manager_set_device_state_changed_cb(g_hWifi, wifi_manager_device_state_changed_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_device_state_changed_cb", WifiManagerGetError(nRet));

	nRet =  wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_is_activated", WifiManagerGetError(nRet));
	if(bActivated == false)
	{
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback_without_mainloop, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
	}
	else
	{
		nRet = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback_without_mainloop, NULL);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deactivate", WifiManagerGetError(nRet));
	}

	RUN_POLLING_LOOP;

	//Target API
	nRet = wifi_manager_unset_device_state_changed_cb(g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_unset_device_state_changed_cb", WifiManagerGetError(nRet));

	if( !g_bWifiManagerCB )
	{
		g_bWifiManagerCBHit = false;
		FPRINTF("[%s:%d] wifi_manager_device_state_changed_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_device_state_changed_callback not invoked!!", __FILE__, __LINE__);
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
		}
		return 1;
	}

	nRet =  wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_device_state_changed_cb", WifiManagerGetError(nRet));
	if (bActivated == false) {
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit)
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
			return 1;
		}
	}

	return 0;
}

//& purpose: Registers the callback called when the connection state is changed.
//& type: auto
/**
* @testcase				ITc_wifi_manager_set_unset_connection_state_changed_cb_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Registers the callback called when the connection state is changed.
* @apicovered			wifi_manager_set_connection_state_changed_cb, wifi_manager_unset_connection_state_changed_cb
* @passcase				When  wifi_manager_set_connection_state_changed_cb, wifi_manager_unset_connection_state_changed_cb API returns 0
* @failcase				If  wifi_manager_set_connection_state_changed_cb, wifi_manager_unset_connection_state_changed_cb returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_set_unset_connection_state_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	bool bActivated = false;
	g_bWifiManagerCBHit = false;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	//Target API
	nRet = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_connection_state_changed_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_connection_state_changed_cb", WifiManagerGetError(nRet));

	nRet = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deactivate", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;

	nRet = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_unset_connection_state_changed_cb", WifiManagerGetError(nRet));

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_connection_state_changed_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_connection_state_changed_callback not invoked!!", __FILE__, __LINE__);
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
		}
		return 1;
	}
	nRet =  wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_device_state_changed_cb", WifiManagerGetError(nRet));
	if (bActivated == false) {
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
			return 1;
		}
	}
	return 0;
}
//& purpose: Registers callback called when the RSSI of connected Wi-Fi is changed.
//& type: auto
/**
* @testcase				ITc_wifi_manager_set_unset_rssi_level_changed_cb_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Registers callback called when the RSSI of connected Wi-Fi is changed.
* @apicovered			wifi_manager_set_rssi_level_changed_cb, wifi_manager_unset_rssi_level_changed_cb
* @passcase				When  wifi_manager_set_rssi_level_changed_cb, wifi_manager_unset_rssi_level_changed_cb API returns 0
* @failcase				If  wifi_manager_set_rssi_level_changed_cb, wifi_manager_unset_rssi_level_changed_cb returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_set_unset_rssi_level_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;
	g_bWifiManagerCB = false;
	bool bActivated = false;
	g_bWifiManagerCBHit = false;

	// precondition
	int nRet = wifi_manager_is_activated(g_hWifi, &bActivated);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_is_activated", WifiManagerGetError(nRet));
	if(bActivated == true)
	{
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_deactivate(g_hWifi, wifi_manager_deactivated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_deactivate", WifiManagerGetError(nRet));
	}

	//Target API
	nRet = wifi_manager_set_rssi_level_changed_cb(g_hWifi, wifi_manager_rssi_level_changed_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_rssi_level_changed_cb", WifiManagerGetError(nRet));

	nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback_without_mainloop, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;

	nRet = wifi_manager_unset_rssi_level_changed_cb(g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_unset_rssi_level_changed_cb", WifiManagerGetError(nRet));

	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_rssi_level_changed_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_rssi_level_changed_callback not invoked!!", __FILE__, __LINE__);
		g_bWifiManagerCBHit = false;
		nRet = wifi_manager_activate(g_hWifi, wifi_manager_activated_callback, NULL);
		RUN_POLLING_LOOP;
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_activate", WifiManagerGetError(nRet));
		if ( !g_bWifiManagerCBHit )
		{
			FPRINTF("[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked\\n", __FILE__, __LINE__);
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_activate failed, error returned = callback function not invoked", __FILE__, __LINE__);
		}
		return 1;
	}
	return 0;
}

//& purpose: Gets the name of the network interface.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_network_interface_name_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Activate WiFi and get the network interface name. If Wi-Fi is not activated immediately
*						Wi-Fi interface name callback will be triggered on Wi-Fi activation.
* @apicovered			wifi_manager_get_network_interface_name
* @passcase				When  wifi_manager_get_network_interface_name API returns 0
* @failcase				If  wifi_manager_get_network_interface_name returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_network_interface_name_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char* pIntfName = NULL;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_network_interface_name", WifiManagerGetError(nRet));

	nRet = wifi_manager_get_network_interface_name(g_hWifi, &pIntfName);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_network_interface_name", WifiManagerGetError(nRet));

	if(pIntfName == NULL)
	{
		FPRINTF("[%s:%d] wifi_manager_get_network_interface_name returned value is not correct!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_get_network_interface_name returned value is not correct!!", __FILE__, __LINE__);
		return 1;
	}

	//FREE_MEMORY(pIntfName);

	return 0;
}

//& purpose: Gets the name of the network interface.
//& type: auto
/**
* @testcase				ITc_wifi_manager_scanned_callback_p
* @since				3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Activate WiFi and get the network interface name. If Wi-Fi is not activated immediately
*						Wi-Fi interface name callback will be triggered on Wi-Fi activation.
* @apicovered			wifi_manager_scanned_callback
* @passcase				When  wifi_manager_scanned_callback API returns 0
* @failcase				If  wifi_manager_scanned_callback returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_scanned_callback_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scanned_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scanned_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}


	return 0;
}

//& purpose: Gets the Wi-Fi scan state.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_scan_state_p
* @since				4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the Wi-Fi scan state.
* @apicovered			wifi_manager_get_scan_state
* @passcase				When  wifi_manager_get_scan_state API returns 0
* @failcase				If  wifi_manager_get_scan_state returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_scan_state_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_scan_state_e eGetScanState;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scanned_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scanned_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	//Target API
	nRet = wifi_manager_get_scan_state(g_hWifi, &eGetScanState);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_scan_state", WifiManagerGetError(nRet));
	FPRINTF("[%s:%d] Test Finished successfully!!!\\n", __FILE__, __LINE__);
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Test Finished successfully!!!", __FILE__, __LINE__);

	return 0;
}

//& purpose: Registers and Unregisters the callback called when the scanning state is changed.
//& type: auto
/**
* @testcase				ITc_wifi_manager_set_unset_scan_state_changed_cb_p
* @since				4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Registers and Unregisters the callback called when the scanning state is changed.
* @apicovered			wifi_manager_set_scan_state_changed_cb, wifi_manager_unset_scan_state_changed_cb
* @passcase				When  wifi_manager_set_scan_state_changed_cb & wifi_manager_unset_scan_state_changed_cb API returns 0
* @failcase				If  wifi_manager_set_scan_state_changed_cb or wifi_manager_unset_scan_state_changed_cb returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_set_unset_scan_state_changed_cb_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	g_bWifiManagerCB = false;
	g_bWifiManagerCBHit = false;

	int nRet = wifi_manager_set_scan_state_changed_cb(g_hWifi, wifi_manager_scan_state_changed_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_set_scan_state_changed_cb", WifiManagerGetError(nRet));

	nRet = wifi_manager_scan(g_hWifi, wifi_manager_scanned_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_scanned_callback", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_scanned_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scanned_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}
	if(!g_bWifiManagerCBHit)
	{
		FPRINTF("[%s:%d] wifi_manager_scan_state_changed_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_scan_state_changed_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}
	nRet = wifi_manager_unset_scan_state_changed_cb(g_hWifi);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_unset_scan_state_changed_cb", WifiManagerGetError(nRet));
	FPRINTF("[%s:%d] Test Finished successfully!!!\\n", __FILE__, __LINE__);
	dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Test Finished successfully!!!", __FILE__, __LINE__);

	return 0;
}


//& purpose: Starts bssid scan asynchronously.
//& type: auto
/**
* @testcase				ITc_wifi_manager_bssid_scan_p
* @since				4.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Starts bssid scan asynchronously.
* @apicovered			wifi_manager_bssid_scan
* @passcase				When  wifi_manager_bssid_scan API returns 0
* @failcase				If  wifi_manager_bssid_scan returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_bssid_scan_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_pre_activate", WifiManagerGetError(nRet));

	g_bWifiManagerCB = false;
	//Target API
	nRet =  wifi_manager_bssid_scan(g_hWifi, wifi_manager_bssid_scan_finished_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_bssid_scan", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_bssid_scan_finished_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_bssid_scan_finished_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Called for each found access point.
//& type: auto
/**
* @testcase				ITc_wifi_manager_foreach_found_bssid_ap_p
* @since				4.0
* @author				SRID(a.pandia1)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Called for each found access point.
* @apicovered			wifi_manager_bssid_scan, wifi_manager_foreach_found_bssid_ap
* @passcase				When  wifi_manager_foreach_found_bssid_ap API returns 0
* @failcase				If  wifi_manager_foreach_found_bssid_ap returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_foreach_found_bssid_ap_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	nTimeoutId = 0;

	int nRet = wifi_manager_pre_activate();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_pre_activate", WifiManagerGetError(nRet));

	g_bWifiManagerCB = false;
	nRet =  wifi_manager_bssid_scan(g_hWifi, wifi_manager_bssid_scan_finished_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_bssid_scan", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_bssid_scan_finished_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_bssid_scan_finished_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	g_bWifiManagerCB = false;
	//Target API
	nRet =  wifi_manager_foreach_found_bssid_ap(g_hWifi, wifi_manager_foreach_found_bssid_ap_callback, NULL);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_foreach_found_bssid_ap", WifiManagerGetError(nRet));

	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_foreach_found_bssid_ap_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_foreach_found_bssid_ap_callback not invoked!!", __FILE__, __LINE__);
		return 1;
	}

	return 0;
}

//& purpose: Getting specific AP multi scan handle and then destroying it
//& type: auto
/**
* @testcase				ITc_wifi_manager_specific_scan_create_and_destroy_p
* @since				4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Initialization of Wi-Fi and  creating  & destroying  specific AP multi scan handle.
* @apicovered			wifi_manager_specific_scan_create, wifi_manager_specific_scan_destroy
* @passcase				When  wifi_manager_specific_scan_create,wifi_manager_specific_scan_destroy API returns 0
* @failcase				If  wifi_manager_specific_scan_create,wifi_manager_specific_scan_destroy returns non zero value
* @precondition			NA
* @postcondition		NA
*/

int ITc_wifi_manager_specific_scan_create_and_destroy_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;

	nRet = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_HANDLE(specific_scan,"wifi_manager_specific_scan_create");
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_create", WifiManagerGetError(nRet), wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Sets specific AP SSID in multi scan handle
//& type: auto
/**
* @testcase				ITc_wifi_manager_specific_scan_set_ssid_p
* @since				4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Setting specific AP SSID in multi scan handle.
* @apicovered			wifi_manager_specific_scan_create, wifi_manager_specific_scan_set_ssid,
*						wifi_manager_specific_scan_destroy.
* @passcase				When  wifi_manager_specific_scan_set_ssid API returns 0
* @failcase				If  wifi_manager_specific_scan_create,wifi_manager_specific_scan_destroy  or
*						wifi_manager_specific_scan_set_ssid fails.
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_specific_scan_set_ssid_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = WIFI_MANAGER_ERROR_NONE;
	char ap_name[CONFIG_VALUE_LEN_MAX];
	wifi_manager_specific_scan_h specific_scan = NULL;

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s\\n", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

	nRet = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_HANDLE(specific_scan,"wifi_manager_specific_scan_create");
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_create", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));
	nRet = wifi_manager_specific_scan_set_ssid(specific_scan, ap_name);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_set_ssid", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_destroy", WifiManagerGetError(nRet));

	return 0;
}
//& purpose: Sets specific scan frequency
//& type: auto
/**
* @testcase				ITc_wifi_manager_specific_scan_set_freq_p
* @since				4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Setting specific frequency through wifi_manager_specific_scan_set_freq api.
* @apicovered			wifi_manager_specific_scan_create,wifi_manager_specific_scan_set_freq ,
*						wifi_manager_specific_scan_destroy.
* @passcase				When  wifi_manager_specific_scan_set_freq API returns 0
* @failcase				If  wifi_manager_specific_scan_create,wifi_manager_specific_scan_destroy  or
*						wifi_manager_specific_scan_set_freq fails ,returnin non zero.
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_specific_scan_set_freq_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;
	int freq =  SET_FREQ;

	nRet = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_HANDLE(specific_scan,"wifi_manager_specific_scan_create");
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_create", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_scan_set_freq(specific_scan, freq);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_set_freq", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose:Starts multi SSID and multi channel specific scan, asynchronously
//& type: auto
/**
* @testcase				ITc_wifi_manager_specific_ap_start_multi_scan_p
* @since				4.0
* @author				SRID(bipin.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @scenario				Scan for specific AP set in multi scan handle. When scan is
*						done the callback is triggered.
* @apicovered			wifi_manager_specific_scan_create,wifi_manager_specific_ap_start_multi_scan ,
*						wifi_manager_specific_scan_destroy,wifi_manager_specific_scan_set_ssid.
* @passcase				When It invokes wifi_manager_multi_scan_callback().
* @failcase				If  any of the basic api including wifi_manager_specific_ap_start_multi_scan API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_specific_ap_start_multi_scan_p(void)
{
	START_TEST_CHECK_INITIALIZE;
	int nRet = WIFI_MANAGER_ERROR_NONE;
	wifi_manager_specific_scan_h specific_scan = NULL;
	char ap_name[CONFIG_VALUE_LEN_MAX];
	g_bWifiManagerCB=false;

	if (GetValueFromConfigFile("WIFI_WPSACCESSPOINTNAME", ap_name, API_NAMESPACE)) {
		FPRINTF("[%s:%d] Values Received ap_name = %s\\n", __FILE__, __LINE__, ap_name);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received ap_name = %s", __FILE__, __LINE__, ap_name);
	} else {
		FPRINTF("[%s:%d] GetValueFromConfigFile returned error\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] Values Received = %s", __FILE__, __LINE__);
		return 1;
	}

	nRet = wifi_manager_specific_scan_create(g_hWifi, &specific_scan);
	CHECK_HANDLE(specific_scan,"wifi_manager_specific_scan_create");
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_create", WifiManagerGetError(nRet), wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_scan_set_ssid(specific_scan, ap_name);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_set_ssid", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));

	nRet = wifi_manager_specific_ap_start_multi_scan(g_hWifi, specific_scan, wifi_manager_multi_scan_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_ap_start_multi_scan", WifiManagerGetError(nRet),wifi_manager_specific_scan_destroy(g_hWifi, specific_scan));
	RUN_POLLING_LOOP;
	if( !g_bWifiManagerCB )
	{
		FPRINTF("[%s:%d] wifi_manager_multi_scan_callback not invoked!!\\n", __FILE__, __LINE__);
		dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] wifi_manager_multi_scan_callback not invoked!!", __FILE__, __LINE__);
		wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
		return 1;
	}

	nRet = wifi_manager_specific_scan_destroy(g_hWifi, specific_scan);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& type: auto
/**
* @testcase>>--->--->---ITc_wifi_manager_set_ip_conflict_detect_enable_p
* @since>--->--->--->---5.0
* @author>-->--->--->---SRID(bipin.k)
* @reviewer>>--->--->---SRID(a.pandia1)
* @type>>--->--->--->---auto
* @scenario>>--->--->---Invoke wifi_manager_set_ip_conflict_detect_enable() with valid parameter.
* @apicovered>-->--->---wifi_manager_set_ip_conflict_detect_enable,wifi_manager_ip_conflict_detect_is_enabled
* @passcase>>--->--->---wifi_manager_set_ip_conflict_detect_enable call is successful
* @failcase>>--->--->---Failure in any of the apis covered
* @precondition>>--->---NA
* @postcondition>--->---NA
*/
int ITc_wifi_manager_set_ip_conflict_detect_enable_p(void)
{
        START_TEST_CHECK_INITIALIZE;
        int nRet;
        bool state;

        nRet = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);
        FPRINTF("[%s:%d] IP conflict detection is %s\\n", __FILE__, __LINE__, state ? "enabled" : "disabled");
        dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d], IP conflict detection is %s", __FILE__, __LINE__, state ? "enabled" : "disabled");
        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ip_conflict_detect_is_enabled", WifiManagerGetError(nRet));
        if (state) //IP conflict detection is enable
        {
                nRet = wifi_manager_set_ip_conflict_detect_enable(g_hWifi, false);
                CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_set_ip_conflict_detect_enable", WifiManagerGetError(nRet));

                nRet = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);
                CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ip_conflict_detect_is_enabled", WifiManagerGetError(nRet));
                FPRINTF("[%s:%d] IP conflict detection is %s\\n", __FILE__, __LINE__, state ? "enabled" : "disabled");
				dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d], IP conflict detection is %s", __FILE__, __LINE__, state ? "enabled" : "disabled");

                if(state != false)
                {
                        FPRINTF("[%s:%d] wifi_manager_set_ip_conflict_detect_enable is not successful!!\\n", __FILE__, __LINE__);
                        return 1;
                }
        }
        else //IP conflict detection is disable
        {
                nRet = wifi_manager_set_ip_conflict_detect_enable(g_hWifi, true);
                CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_set_ip_conflict_detect_enable", WifiManagerGetError(nRet));

                nRet = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);
                CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ip_conflict_detect_is_enabled", WifiManagerGetError(nRet));
                FPRINTF("[%s:%d] IP conflict detection is %s\\n", __FILE__, __LINE__, state ? "enabled" : "disabled");
				dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d], IP conflict detection is %s", __FILE__, __LINE__, state ? "enabled" : "disabled");

                if(state != true)
                {
                        FPRINTF("[%s:%d] wifi_manager_set_ip_conflict_detect_enable is not successful!!\\n", __FILE__, __LINE__);
                        return 1;
                }
        }
        return 0;
}
//& type: auto
/**
* @testcase>>--->--->---ITc_wifi_manager_ip_conflict_detect_is_enabled_p
* @since>--->--->--->---5.0
* @author>-->--->--->---SRID(bipin.k)
* @reviewer>>--->--->---SRID(a.pandia1)
* @type>>--->--->--->---auto
* @scenario>>--->--->---Invoke wifi_manager_ip_conflict_detect_is_enabled() with valid parameter.
* @apicovered>-->--->---wifi_manager_ip_conflict_detect_is_enabled
* @passcase>>--->--->---Checks whether IP conflict detection can be  enabled.
* @failcase>>--->--->---Failure in any of the apis covered
* @precondition>>--->---NA
* @postcondition>--->---NA
*/
int ITc_wifi_manager_ip_conflict_detect_is_enabled_p(void)
{
        START_TEST_CHECK_INITIALIZE;
        bool state;

        int nRet = wifi_manager_ip_conflict_detect_is_enabled(g_hWifi, &state);

        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ip_conflict_detect_is_enabled", WifiManagerGetError(nRet));

        return 0;
}

//& type: auto
/**
* @testcase>>--->--->---ITc_wifi_manager_get_ip_conflict_state_p
* @since>--->--->--->---5.0
* @author>-->--->--->---SRID(bipin.k)
* @reviewer>>--->--->---SRID(a.pandia1)
* @type>>--->--->--->---auto
* @scenario>>--->--->---Invoking  wifi_manager_get_ip_conflict_state
* @apicovered>-->--->---wifi_manager_get_ip_conflict_state
* @passcase>>--->--->---wifi_manager_get_ip_conflict_state returns success
* @failcase>>--->--->---Failure in any of the apis covered
* @precondition>>--->---NA
* @postcondition>--->---NA
*/
int ITc_wifi_manager_get_ip_conflict_state_p(void)
{
        START_TEST_CHECK_INITIALIZE;
        wifi_manager_ip_conflict_state_e state;

        int nRet = wifi_manager_get_ip_conflict_state(g_hWifi, &state);
        if((state < WIFI_MANAGER_IP_CONFLICT_STATE_UNKNOWN) || (state > WIFI_MANAGER_IP_CONFLICT_STATE_CONFLICT_DETECTED))
        {
                FPRINTF("[%s:%d] wifi_manager_get_ip_conflict_state is out of range!!\\n", __FILE__, __LINE__);
                return 1;
        }

        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_ip_conflict_state", WifiManagerGetError(nRet));

        return 0;
}
//& purpose:Adds and Removes the Wi-Fi Vendor Specific Information Element (VSIE) to a specific frame type
//& type: auto
/**
* @testcase				ITc_wifi_manager_add_remove_vsie_p
* @since				5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Adds and Removes the Wi-Fi Vendor Specific Information Element (VSIE) to a specific frame type
* @apicovered			wifi_manager_add_vsie, wifi_manager_remove_vsie
* @passcase				When both API get pass
* @failcase				If  any of the basic api including wifi_manager_specific_ap_start_multi_scan API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_add_remove_vsie_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet;
	const char *vsie_str = "dd0411223301";
	wifi_manager_vsie_frames_e eVsieFrame []={	WIFI_MANAGER_VSIE_FRAME_PROBE_REQ,
												WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ,
												//WIFI_MANAGER_VSIE_FRAME_REASSOC,
												//WIFI_MANAGER_VSIE_FRAME_AUTH_REQ,
												//WIFI_MANAGER_VSIE_FRAME_ACTION,
											};

	int nLength = sizeof(eVsieFrame)/sizeof(eVsieFrame[0]);
	for(int i =0 ;i<nLength; i++)
	{
		nRet = wifi_manager_add_vsie(g_hWifi, eVsieFrame[i], vsie_str);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_add_vsie", WifiManagerGetError(nRet));

		nRet = wifi_manager_remove_vsie(g_hWifi, eVsieFrame[i], vsie_str);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_remove_vsie", WifiManagerGetError(nRet));
	}

	return 0;
}

//& purpose:Gets the Wi-Fi Vendor Specific Information Elements (VSIE) from a specific frame.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_vsie_p
* @since				5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the Wi-Fi Vendor Specific Information Elements (VSIE) from a specific frame.
* @apicovered			wifi_manager_get_vsie
* @passcase				When API get pass
* @failcase				If any of the basic api including wifi_manager_specific_ap_start_multi_scan API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_vsie_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet;
	char *vsie_str = "dd0411223301";
	char *getvsie_Str = NULL;
	wifi_manager_vsie_frames_e eVsieFrame []={	WIFI_MANAGER_VSIE_FRAME_PROBE_REQ,
												WIFI_MANAGER_VSIE_FRAME_ASSOC_REQ,
												//WIFI_MANAGER_VSIE_FRAME_REASSOC,
												//WIFI_MANAGER_VSIE_FRAME_AUTH_REQ,
												//WIFI_MANAGER_VSIE_FRAME_ACTION,
											};

	int nLength = sizeof(eVsieFrame)/sizeof(eVsieFrame[0]);
	for(int i =0; i<nLength; i++)
	{
		nRet = wifi_manager_add_vsie(g_hWifi, eVsieFrame[i], vsie_str);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_add_vsie", WifiManagerGetError(nRet));

		nRet = wifi_manager_get_vsie(g_hWifi,eVsieFrame[i],&getvsie_Str);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_vsie", WifiManagerGetError(nRet));

		nRet = wifi_manager_remove_vsie(g_hWifi, eVsieFrame[i], vsie_str);
		CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_remove_vsie", WifiManagerGetError(nRet));

		FREE_MEMORY(getvsie_Str);
	}

	return 0;
}

//& purpose: Gets the WPS generated PIN code.
//& type: auto
/**
* @testcase				ITc_wifi_manager_get_wps_generated_pin_p
* @since				5.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @scenario				Gets the WPS generated PIN code.
* @apicovered			wifi_manager_get_wps_generated_pin
* @passcase				When  wifi_manager_get_wps_generated_pin API returns 0
* @failcase				If  wifi_manager_get_wps_generated_pin returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_get_wps_generated_pin_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	char *getWpsPin = NULL;

	//Target API
	int nRet = wifi_manager_get_wps_generated_pin(g_hWifi, &getWpsPin);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, " wifi_manager_get_wps_generated_pin", WifiManagerGetError(nRet));
	if(getWpsPin == NULL)
	{
		 FPRINTF("[%s:%d] getWpsPin value is NULL\\n", __FILE__, __LINE__);		
		 return 1;
	}
	FREE_MEMORY(getWpsPin);

	return 0;
}

//& purpose: Wifi Manager forgot AP asynchrounously
//& type: auto
/**
* @testcase				ITc_wifi_manager_forget_ap_async_p
* @since				5.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(nibha.sharma)
* @type					auto
* @scenario				Wifi Manager forgot AP asynchrounously.
* @apicovered			wifi_manager_forget_ap_async
* @passcase				When  wifi_manager_forget_ap_async API returns 0
* @failcase				If  wifi_manager_forget_ap_async returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_forget_ap_async_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	wifi_manager_ap_h hAP = NULL;
	int nRet = -1;

	nRet = wifi_manager_pre_connect();
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_pre_connect", WifiManagerGetError(nRet));

	nRet = wifi_manager_get_connected_ap(g_hWifi, &hAP);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_connected_ap", WifiManagerGetError(nRet));
	CHECK_HANDLE(hAP, "wifi_manager_get_connected_ap");

	nRet = wifi_manager_set_connection_state_changed_cb(g_hWifi, wifi_manager_connection_state_changed_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_set_connection_state_changed_cb", WifiManagerGetError(nRet), wifi_manager_ap_destroy(hAP));

	//Target API
	nRet = wifi_manager_forget_ap_async(g_hWifi, hAP,
					   wifi_manager_forget_ap_async_callback, NULL);
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_forget_ap_async", WifiManagerGetError(nRet), wifi_manager_unset_connection_state_changed_cb(g_hWifi);wifi_manager_ap_destroy(hAP));
	RUN_POLLING_LOOP;
	if (!g_nCallbackRet)
	{
		FPRINTF("[%s:%d] wifi_manager_forget_ap_async callback not invoked\\n", __FILE__, __LINE__);
		wifi_manager_unset_connection_state_changed_cb(g_hWifi);
		wifi_manager_ap_destroy(hAP);
		return 1;
	}

	nRet = wifi_manager_pre_connect();
	PRINT_RESULT_CLEANUP(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_pre_connect", WifiManagerGetError(nRet), wifi_manager_unset_connection_state_changed_cb(g_hWifi);wifi_manager_ap_destroy(hAP));

	nRet = wifi_manager_unset_connection_state_changed_cb(g_hWifi);
	PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_unset_connection_state_changed_cb", WifiManagerGetError(nRet));

	nRet = wifi_manager_ap_destroy(hAP);
	PRINT_RESULT_NORETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_destroy", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: To get whether 5Ghz Wi-Fi band is supported
//& type: auto
/**
* @testcase				ITc_wifi_manager_is_5ghz_band_supported_p
* @since				5.5
* @author				SRID(karanam.s)
* @reviewer				SRID(manoj.g2)
* @type					auto
* @scenario				Gets whether 5Ghz Wi-Fi band is supported
* @apicovered			wifi_manager_is_5ghz_band_supported
* @passcase				When  wifi_manager_is_5ghz_band_supported API returns 0
* @failcase				If  wifi_manager_is_5ghz_band_supported returns non zero value
* @precondition			NA
* @postcondition		NA
*/
int ITc_wifi_manager_is_5ghz_band_supported_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	bool bSupported = false;
	int nRet = wifi_manager_is_5ghz_band_supported(g_hWifi, &bSupported);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_is_5ghz_band_supported", WifiManagerGetError(nRet));

	return 0;
}

//& purpose: Gets the maximum number of SSIDs supported by the Wi-Fi chipset for the scan operation.
//& type: auto
/**
* @testcase			ITc_wifi_manager_specific_scan_get_max_ssids_p
* @since			5.5
* @author			SRID(j.abhishek)
* @reviewer			SRID(shobhit.v)
* @type			auto
* @scenario			Gets the maximum number of SSIDs supported by the Wi-Fi chipset for the scan operation.
* @apicovered			wifi_manager_specific_scan_get_max_ssids
* @passcase			When wifi_manager_specific_scan_get_max_ssids API returns 0
* @failcase			If wifi_manager_specific_scan_get_max_ssids returns non zero value
* @precondition		wifi manager should be initialized.
* @postcondition		NA
*/
int ITc_wifi_manager_specific_scan_get_max_ssids_p(void)
{
	START_TEST_CHECK_INITIALIZE;

	int nRet = WIFI_MANAGER_ERROR_NONE;
	int nMaxScanSSIDs = 0;

	//Target API
	nRet = wifi_manager_specific_scan_get_max_ssids(g_hWifi, &nMaxScanSSIDs);
	CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_specific_scan_get_max_ssids", WifiManagerGetError(nRet));
	FPRINTF("[%s:%d] wifi_manager_specific_scan_get_max_ssids return Maximum SSID count=%d \\n", __FILE__, __LINE__, nMaxScanSSIDs);
	return 0;
}


//& purpose: To Check weather wifi ap is hidden
//& type: auto
/**
* @testcase                             ITc_wifi_manager_ap_is_hidden_p
* @since                                5.5
* @author                               SRID(manoj.g2)
* @reviewer                             SRID(shobhit.v)
* @type                                 auto
* @scenario                             To Check weather wifi ap is hidden
* @apicovered                           wifi_manager_ap_is_hidden
* @passcase                             When   wifi_manager_ap_is_hidden and  Precondition API returns 0
* @failcase                             If  wifi_manager_ap_is_hidden returns non zero value
* @precondition                 NA
* @postcondition                NA
*/
int ITc_wifi_manager_ap_is_hidden_p(void)
{
        START_TEST_CHECK_INITIALIZE;

        wifi_manager_ap_h hAP = NULL;
	bool isHidden = false;
        int nRet = -1;

        nRet = wifi_manager_pre_connect();
        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_pre_connect", WifiManagerGetError(nRet));

        nRet = wifi_manager_get_connected_ap(g_hWifi, &hAP);
        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_get_connected_ap", WifiManagerGetError(nRet));
	CHECK_HANDLE(hAP,"wifi_manager_get_connected_ap");

	nRet = wifi_manager_ap_is_hidden(hAP, &isHidden);
        CHECK_RETURN(WIFI_MANAGER_ERROR_NONE, nRet, "wifi_manager_ap_is_hidden", WifiManagerGetError(nRet));
	return 0;
}
/** @} */

