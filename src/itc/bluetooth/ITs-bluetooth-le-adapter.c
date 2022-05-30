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

#include "ITs-bluetooth-common.h"

static int manufacturer_id = 117;
static char *manufacture = NULL;
static char manufacture_0[] = {0x0, 0x0, 0x0, 0x0};
static char service_data[] = {0x01, 0x02, 0x03};

/**
 * @function 		gmain_loop_quit_idle
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
static gboolean gmain_loop_quit_idle(gpointer p)
{

	g_main_loop_quit(g_pMainLoop);
	g_main_loop_unref(g_pMainLoop);
	g_pMainLoop = NULL;
	return G_SOURCE_REMOVE;
}

/** @addtogroup itc-bluetooth
*  @ingroup itc
*  @{
*/
/**
 * @brief Callback funtions
 */
static void Bluetooth_bt_adapter_le_scan_result_cb(int result,bt_adapter_le_device_scan_result_info_s *info, void *user_data)
{
	bt_adapter_le_packet_type_e pkt_type = BT_ADAPTER_LE_PACKET_ADVERTISING;
	char **uuids = NULL;
	char *device_name = NULL;
	int tx_power_level = 0;
	bt_adapter_le_service_data_s *data_list = NULL;
	int appearance = 0;
	int manufacturer_id = 0;
	char *manufacturer_data = NULL;
	int manufacturer_data_len = 0;
	int count = 0;

	if (g_bCallbackResult == true)
	{
		FPRINTF("\\n[Line : %d][%s] Already PASS the testcase, so quit g_main_loop", __LINE__, API_NAMESPACE);
		g_idle_add(gmain_loop_quit_idle, NULL);
		return;
	}

	if (info == NULL)
	{
		FPRINTF("\\n[Line : %d][%s] No discovery_info!", __LINE__, API_NAMESPACE);
		return ;
	}

	FPRINTF("\\n%s Adv %d Scan resp %d RSSI %d Addr_type %d", info->remote_address, info->adv_data_len, info->scan_data_len, info->rssi, info->address_type);

	if (info->adv_data_len > 31 || info->scan_data_len > 31)
	{
		FPRINTF("\\n[Line : %d][%s] info->adv_data_len or info->scan_data_len exceed data length", __LINE__, API_NAMESPACE);
		bt_adapter_le_stop_scan();
		return;
	}

	g_bCallbackResult = true;

	int nRet = bt_adapter_le_get_scan_result_service_uuids(info, pkt_type, &uuids, &count);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA )
	{
		int i;
		for (i = 0; i < count; i++)
		{
			if (nRet==BT_ERROR_NO_DATA) {
				FPRINTF("No data");
			}
			else {
				FPRINTF("\\nUUID[%d] = %s", i + 1, uuids[i]);
			}

			if( nRet == BT_ERROR_NONE && uuids[i] != NULL){
				free(uuids[i]);
				uuids[i] = NULL;
			}
		}
		if(nRet == BT_ERROR_NONE && count > 0 && uuids != NULL){
			free(uuids);
			uuids = NULL;
		}
	} else {
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_service_uuids", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_device_name(info, pkt_type, &device_name);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		if (nRet==BT_ERROR_NO_DATA) {
			FPRINTF(" device_name No data");
		} else {
			FPRINTF("\\nDevice name = %s", device_name);
		}
		if(device_name != NULL)
			free(device_name);
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_device_name", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_tx_power_level(info, pkt_type, &tx_power_level);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		if (nRet==BT_ERROR_NO_DATA) {
			FPRINTF("No data");
		} else {
			FPRINTF("\\nTX Power level = %d", tx_power_level);
		}
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_tx_power_level", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_service_solicitation_uuids(info, pkt_type, &uuids, &count);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		int i;
		for (i = 0; i < count; i++) {
			if (nRet==BT_ERROR_NO_DATA) {
				FPRINTF("No data");
			} else {
				FPRINTF("\\nSolicitation UUID[%d] = %s", i + 1, uuids[i]);
			}
			if(nRet == BT_ERROR_NONE && uuids[i] != NULL){
				free(uuids[i]);
				uuids[i] = NULL;
			}
		}
		if(nRet == BT_ERROR_NONE && count > 0 && uuids != NULL){
			free(uuids);
			uuids = NULL;
		}
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_service_solicitation_uuids", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_service_data_list(info, pkt_type, &data_list, &count);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		int i;
		for (i = 0; i < count; i++)
		{
			if (nRet==BT_ERROR_NO_DATA) {
				FPRINTF("No data");
			} else {
				FPRINTF("\\nService Data[%d] = [0x%2.2X%2.2X:0x%.2X...]", i + 1, data_list[i].service_uuid[0], data_list[i].service_uuid[1], data_list[i].service_data[0]);
			}
		}
		if(nRet == BT_ERROR_NONE && count > 0 && data_list != NULL){
			bt_adapter_le_free_service_data_list(data_list, count);
		}
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_service_data_list", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_appearance(info, pkt_type, &appearance);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		if (nRet==BT_ERROR_NO_DATA) {
				FPRINTF(" appearance No data");
		} else {
			FPRINTF("\\nAppearance = %d", appearance);
		}
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_appearance", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	nRet = bt_adapter_le_get_scan_result_manufacturer_data(info, pkt_type, &manufacturer_id, &manufacturer_data, &manufacturer_data_len);
	if ( nRet == BT_ERROR_NONE || nRet == BT_ERROR_NO_DATA)
	{
		if (nRet==BT_ERROR_NO_DATA) {
				FPRINTF(" manufacturer_data No data");
		} else {
			FPRINTF("\\nManufacturer data[ID:%.4X, 0x%.2X%.2X...(len:%d)]", manufacturer_id, manufacturer_data[0], manufacturer_data[1], manufacturer_data_len);
		}
		if (nRet == BT_ERROR_NONE && manufacturer_data != NULL )
		{
			free(manufacturer_data);
		}
	}
	else
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, returned %s error", __LINE__, API_NAMESPACE, "bt_adapter_le_get_scan_result_manufacturer_data", BluetoothGetError(nRet));
		g_bCallbackResult = false;
		return;
	}

	return;
}

/**
* @brief Callback funtions
*/
static void Bluetooth_bt_adapter_le_advertising_state_changed_cb(int result,
		bt_advertiser_h advertiser, bt_adapter_le_advertising_state_e adv_state, void *user_data)
{
	FPRINTF("Result : %d", result);
	FPRINTF("Advertiser : %p", advertiser);
	FPRINTF("Advertising %s [%d]", adv_state == BT_ADAPTER_LE_ADVERTISING_STARTED ?
				"started" : "stopped", adv_state);
}

/**
 * @brief Callback funtions
 */
static void Bluetooth_bt_adapter_le_scan_start_stop_result_cb(int result,bt_adapter_le_device_scan_result_info_s *info, void *user_data)
{
	g_bCallbackResult = true;
	FPRINTF("\\n[Line : %d][%s] Bluetooth_bt_adapter_le_scan_start_stop_result_cb  called successfully!", __LINE__ ,API_NAMESPACE);
	g_idle_add(gmain_loop_quit_idle, NULL);
	return;
}


/**
* @function 		ITs_bluetooth_adapter_le_startup
* @description	 	Called before each test, Bluetooth is initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_adapter_le_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	int nRetVal = BT_ERROR_NONE;

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_FEATURE, API_NAMESPACE) )
	{
		g_bBluetoothIsSupported = false;
	}
	else
	{
		g_bBluetoothIsSupported = true;
	}

	nRetVal = bt_initialize();
	if ( false == g_bBluetoothIsSupported )
	{
		if ( nRetVal != BT_ERROR_NOT_SUPPORTED )
		{
			g_bBluetoothMismatch = true;
		}
		else
		{
			g_bBluetoothNotSupported = true;
		}
		return;
	}

	if ( nRetVal != BT_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] Bluetooth initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		g_bBluetoothInit = false;
	}
	else
	{
		FPRINTF("[Line : %d][%s] Bluetooth initialized successfully\\n", __LINE__, API_NAMESPACE);
		g_bBluetoothInit = true;
	}

	if ( !TCTCheckSystemInfoFeatureSupported(BLUETOOTH_LE_FEATURE, API_NAMESPACE) )
	{
		g_bBluetoothIsLESupported = false;
	}
	else
	{
		g_bBluetoothIsLESupported = true;
	}
	return;
}

/**
* @function 		ITs_bluetooth_adapter_le_cleanup
* @description	 	Called after each test, Bluetooth is de-initialized
* @parameter		NA
* @return 			NA
*/
void ITs_bluetooth_adapter_le_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Bluetooth_p\\n", __LINE__, API_NAMESPACE);
#endif
	if ( g_bBluetoothInit )
	{
		int nRetVal = bt_deinitialize();
		if ( nRetVal != BT_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialization failed, error returned = %s\\n", __LINE__, API_NAMESPACE, BluetoothGetError(nRetVal));
		}
		else
		{
			FPRINTF("[Line : %d][%s] Bluetooth de-initialized successfully\\n", __LINE__, API_NAMESPACE);
		}
	}

	if ( g_pMainLoop )
	{
		g_main_loop_quit(g_pMainLoop);
	}
	sleep(SLEEP_TIME);

	return;
}


//& purpose: Create advertiser to advertise device's existence or respond to LE scanning reqeust and destroy advertiser
//& type: auto
/**
* @testcase 			ITc_bluetooth_adapter_bt_adapter_le_create_destroy_advertiser_p
* @since_tizen			2.3
* @type 				auto
* @description			Create advertiser to advertise device's existence or respond to LE scanning reqeust and destroy advertiser
* @scenario				Create advertiser\n
*						Destroy advertiser
* @apicovered			bt_adapter_le_create_advertiser and bt_adapter_le_destroy_advertiser
* @passcase				When bt_adapter_le_create_advertiser and bt_adapter_le_destroy_advertiser is successful
* @failcase				If targest APIs bt_adapter_le_create_advertiser or bt_adapter_le_destroy_advertiser fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bluetooth_adapter_bt_adapter_le_create_destroy_advertiser_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	
	int nRetVal = bt_adapter_le_create_advertiser(&advertiser);
	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRetVal, "bt_adapter_le_create_advertiser", BluetoothGetError(nRetVal));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_le_create_advertiser", BluetoothGetError(nRetVal));

	if ( advertiser == NULL )
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_create_advertiser failed. advertiser value is NULL.\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	nRetVal = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRetVal, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRetVal));
	return 0;
}

//& purpose: To test bt_adapter_le_start_scan
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_start_stop_scan_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_start_scan
 * @scenario			Call bt_adapter_le_start_scan
 * @apicovered			bt_adapter_le_start_scan, bt_adapter_le_stop_scan
 * @passcase			If target API bt_adapter_le_start_scan return 0
 * @failcase			If target API bt_adapter_le_start_scan return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_start_stop_scan_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	g_bCallbackResult = false;

	int nRet = bt_adapter_le_start_scan(Bluetooth_bt_adapter_le_scan_start_stop_result_cb,NULL);
	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_start_scan", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_start_scan", BluetoothGetError(nRet));
	g_pMainLoop = g_main_loop_new(NULL, false);

	nTimeoutId = g_timeout_add(CALLBACK_DELAY, TimeoutFunction, g_pMainLoop);
	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTimeoutId);

	if ( g_bCallbackResult == false )
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, g_bCallbackResult is false", __LINE__ ,API_NAMESPACE, "bt_adapter_le_start_scan");
	}

	nRet =  bt_adapter_le_stop_scan();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_stop_scan", BluetoothGetError(nRet));
	WAIT(SHORT_DELAY);
	return 0;
}

//& purpose: To test all le get APIs
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_get_scan_info_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_start_scan
 * @scenario			Call bt_adapter_le_start_scan
 * @apicovered			bt_adapter_le_start_scan , bt_adapter_le_stop_scan
 * @passcase			If target API bt_adapter_le_start_scan return 0
 * @failcase			If target API bt_adapter_le_start_scan return 1
 * @precondition		Bluetooth must be initialized
 * @pos-condition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_get_scan_info_p(void)
{
	START_TEST;

	int nTimeoutId = 0;
	g_bCallbackResult = false;

	int nRet = bt_adapter_le_start_scan(Bluetooth_bt_adapter_le_scan_result_cb,NULL);
	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_start_scan", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_start_scan", BluetoothGetError(nRet));
	g_pMainLoop = g_main_loop_new(NULL, false);
	nTimeoutId = g_timeout_add(CALLBACK_DELAY, TimeoutFunction, g_pMainLoop);

	g_main_loop_run(g_pMainLoop);
	g_source_remove(nTimeoutId);

	if ( g_bCallbackResult == false )
	{
		FPRINTF("\\n[Line : %d][%s] %s failed, g_bCallbackResult is false", __LINE__, API_NAMESPACE, "bt_adapter_le_start_scan");
	}

	nRet =  bt_adapter_le_stop_scan();
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_stop_scan", BluetoothGetError(nRet));
	WAIT(SHORT_DELAY);
	return 0;
}

//& purpose: To test bt_adapter_le_add_advertising_service_uuid
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_add_advertising_service_uuid_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_add_advertising_service_uuid
 * @scenario			Call bt_adapter_le_add_advertising_service_uuid
 * @apicovered			bt_adapter_le_add_advertising_service_uuid
 * @passcase			If target API bt_adapter_le_add_advertising_service_uuid return 0
 * @failcase			If target API bt_adapter_le_add_advertising_service_uuid return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_add_advertising_service_uuid_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	const char *time_svc_uuid_16 = "1805";
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_add_advertising_service_uuid(advertiser,BT_ADAPTER_LE_PACKET_ADVERTISING, time_svc_uuid_16);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_add_advertising_service_uuid", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_add_advertising_service_solicitation_uuid
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_add_advertising_service_solicitation_uuid_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_add_advertising_service_solicitation_uuid
 * @scenario			Call bt_adapter_le_add_advertising_service_solicitation_uuid
 * @apicovered			bt_adapter_le_add_advertising_service_solicitation_uuid
 * @passcase			If target API bt_adapter_le_add_advertising_service_solicitation_uuid return 0
 * @failcase			If target API bt_adapter_le_add_advertising_service_solicitation_uuid return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_add_advertising_service_solicitation_uuid_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	const char *heart_rate_svc_uuid_16 = "180d";
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_add_advertising_service_solicitation_uuid(advertiser,BT_ADAPTER_LE_PACKET_ADVERTISING, heart_rate_svc_uuid_16);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_add_advertising_service_solicitation_uuid", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_add_advertising_service_data
//& type: auto
/**
 * @testcase 				ITc_bt_adapter_le_add_advertising_service_data_p
 * @since_tizen				2.3.1
 * @author					SRID(manoj.g2)
 * @reviewer				SRID(gupta.sanjay)
 * @type 					Positive
 * @description				To test bt_adapter_le_add_advertising_service_data
 * @scenario				Call bt_adapter_le_add_advertising_service_data
 * @apicovered			   	bt_adapter_le_add_advertising_service_data
 * @passcase				If target API bt_adapter_le_add_advertising_service_data return 0
 * @failcase				If target API bt_adapter_le_add_advertising_service_data return 1
 * @precondition			Bluetooth must be initialized
 * @postcondition		   	Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_add_advertising_service_data_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	char service_data[] = {0x01, 0x02, 0x03};
	const char *time_svc_uuid_16 = "1805";
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_add_advertising_service_data(advertiser,BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, time_svc_uuid_16,service_data, sizeof(service_data));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_add_advertising_service_data", BluetoothGetError(nRet), bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_set_advertising_appearance
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_set_advertising_appearance_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_set_advertising_appearance
 * @scenario			Call bt_adapter_le_set_advertising_appearance
 * @apicovered			bt_adapter_le_set_advertising_appearance
 * @passcase			If target API bt_adapter_le_set_advertising_appearance	return 0
 * @failcase			If target API bt_adapter_le_set_advertising_appearance	 return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_advertising_appearance_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int appearance = 192;  // 192 is generic watch
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_set_advertising_appearance(advertiser,	BT_ADAPTER_LE_PACKET_ADVERTISING, appearance);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, " bt_adapter_le_set_advertising_appearance", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_add_advertising_manufacturer_data
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_add_advertising_manufacturer_data_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_add_advertising_manufacturer_data
 * @scenario			Call bt_adapter_le_add_advertising_manufacturer_data
 * @apicovered			bt_adapter_le_add_advertising_manufacturer_data
 * @passcase			If target API bt_adapter_le_add_advertising_manufacturer_data	return 0
 * @failcase			If target API bt_adapter_le_add_advertising_manufacturer_data	return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_add_advertising_manufacturer_data_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int manufacturer_id = 117;
	char *manufacture = NULL;
	char manufacture_0[] = {0x0, 0x0, 0x0, 0x0};
	manufacture = manufacture_0;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_add_advertising_manufacturer_data(advertiser,BT_ADAPTER_LE_PACKET_SCAN_RESPONSE,manufacturer_id,manufacture, sizeof(manufacture_0));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_add_advertising_manufacturer_dat", BluetoothGetError(nRet), bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_set_advertising_device_name
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_set_advertising_device_name_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_set_advertising_device_name
 * @scenario			Call bt_adapter_le_set_advertising_device_name
 * @apicovered			bt_adapter_le_set_advertising_device_name
 * @passcase			If target API bt_adapter_le_set_advertising_device_name	return 0
 * @failcase			If target API bt_adapter_le_set_advertising_device_name  return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_advertising_device_name_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_set_advertising_device_name(advertiser,BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, true);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_set_advertising_device_name", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_set_advertising_tx_power_level
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_set_advertising_tx_power_level_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_set_advertising_tx_power_level
 * @scenario			Call bt_adapter_le_set_advertising_tx_power_level
 * @apicovered			bt_adapter_le_set_advertising_tx_power_level
 * @passcase			If target API bt_adapter_le_set_advertising_tx_power_level	    return 0
 * @failcase			If target API bt_adapter_le_set_advertising_tx_power_level	    return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_advertising_tx_power_level_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_set_advertising_tx_power_level(advertiser,BT_ADAPTER_LE_PACKET_ADVERTISING, true);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_set_advertising_tx_power_level", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_start_advertising_new
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_start_advertising_new_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_start_advertising_new
 * @scenario			Call bt_adapter_le_start_advertising_new
 * @apicovered			bt_adapter_le_start_advertising_new
 * @passcase			If target API bt_adapter_le_start_advertising_new	    return 0
 * @failcase			If target API bt_adapter_le_start_advertising_new	    return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_start_advertising_new_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_advertising_state_changed_cb cb;
	const char *time_svc_uuid_16 = "1805";
	const char *battery_svc_uuid_16 = "180f";
	cb = Bluetooth_bt_adapter_le_advertising_state_changed_cb;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	/* add advertising data start*/
	nRet = bt_adapter_le_add_advertising_service_uuid(advertiser,
							BT_ADAPTER_LE_PACKET_ADVERTISING, time_svc_uuid_16);

	nRet = bt_adapter_le_add_advertising_service_uuid(advertiser,
					BT_ADAPTER_LE_PACKET_ADVERTISING,  battery_svc_uuid_16);

	nRet = bt_adapter_le_add_advertising_service_data(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, time_svc_uuid_16,
					service_data, sizeof(service_data));

	nRet = bt_adapter_le_set_advertising_device_name(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, true);

	manufacture = manufacture_0;
	nRet = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE,
					manufacturer_id,
					manufacture, sizeof(manufacture_0));
	/* add advertising data end */

	nRet = bt_adapter_le_start_advertising_new(advertiser, cb, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_start_advertising_new", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	/* Post condition: We don't need to check the result for the post condition */
	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	return 0;
}

//& purpose: To test bt_adapter_le_set_advertising_mode
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_set_advertising_mode_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_set_advertising_mode
 * @scenario			Call bt_adapter_le_set_advertising_mode
 * @apicovered			bt_adapter_le_set_advertising_mode
 * @passcase			If target API bt_adapter_le_set_advertising_mode	    return 0
 * @failcase			If target API bt_adapter_le_set_advertising_mode	    return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_advertising_mode_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int mode = BT_ADAPTER_LE_ADVERTISING_MODE_BALANCED;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_set_advertising_mode(advertiser, mode);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, " bt_adapter_le_set_advertising_mode", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_set_advertising_connectable
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_set_advertising_connectable_p
 * @since_tizen			2.3.1
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_set_advertising_connectable
 * @scenario			Call bt_adapter_le_set_advertising_connectable
 * @apicovered			bt_adapter_le_set_advertising_connectable
 * @passcase			If target API bt_adapter_le_set_advertising_connectable return 0
 * @failcase			If target API bt_adapter_le_set_advertising_connectable return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_advertising_connectable_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	bool connectable = true;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_set_advertising_connectable(advertiser, connectable);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_set_advertising_connectable(", BluetoothGetError(nRet) ,bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_stop_advertising
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_stop_advertising_p
 * @since_tizen			2.3
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_stop_advertising
 * @scenario			Call bt_adapter_le_stop_advertising
 * @apicovered			bt_adapter_le_stop_advertising
 * @passcase			If target API bt_adapter_le_stop_advertising	    return 0
 * @failcase			If target API bt_adapter_le_stop_advertising	    return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_stop_advertising_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	bt_adapter_le_advertising_state_changed_cb cb;
	const char *time_svc_uuid_16 = "1805";
	const char *battery_svc_uuid_16 = "180f";

	cb = Bluetooth_bt_adapter_le_advertising_state_changed_cb;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	/* add advertising data start*/
	nRet = bt_adapter_le_add_advertising_service_uuid(advertiser,
							BT_ADAPTER_LE_PACKET_ADVERTISING, time_svc_uuid_16);

	nRet = bt_adapter_le_add_advertising_service_uuid(advertiser,
					BT_ADAPTER_LE_PACKET_ADVERTISING,  battery_svc_uuid_16);

	nRet = bt_adapter_le_add_advertising_service_data(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, time_svc_uuid_16,
					service_data, sizeof(service_data));

	nRet = bt_adapter_le_set_advertising_device_name(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, true);

	manufacture = manufacture_0;
	nRet = bt_adapter_le_add_advertising_manufacturer_data(advertiser,
					BT_ADAPTER_LE_PACKET_SCAN_RESPONSE,
					manufacturer_id,
					manufacture, sizeof(manufacture_0));
	/* add advertising data end */

	nRet = bt_adapter_le_start_advertising_new(advertiser, cb, NULL);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_start_advertising_new", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_stop_advertising(advertiser);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_stop_advertising", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	/* Post condition: We don't need to check the result for the post condition */
	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	return 0;
}

//& purpose: To test bt_adapter_le_clear_advertising_data
//& type: auto
/**
 * @testcase 			ITc_bt_adapter_le_clear_advertising_data_p
 * @since_tizen			2.3
 * @author				SRID(manoj.g2)
 * @reviewer			SRID(gupta.sanjay)
 * @type 				Positive
 * @description			To test bt_adapter_le_clear_advertising_data
 * @scenario			Call bt_adapter_le_clear_advertising_data
 * @apicovered			bt_adapter_le_clear_advertising_data
 * @passcase			If target API bt_adapter_le_clear_advertising_data	    return 0
 * @failcase			If target API bt_adapter_le_clear_advertising_data	    return 1
 * @precondition		Bluetooth must be initialized
 * @postcondition		Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_clear_advertising_data_p(void)
{
	START_TEST;

	bt_advertiser_h advertiser = NULL;
	int nRet = bt_adapter_le_create_advertiser(&advertiser);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_create_advertiser", BluetoothGetError(nRet));

	nRet = bt_adapter_le_clear_advertising_data(advertiser, BT_ADAPTER_LE_PACKET_ADVERTISING);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_clear_advertising_data", BluetoothGetError(nRet),bt_adapter_le_destroy_advertiser(advertiser));

	nRet = bt_adapter_le_destroy_advertiser(advertiser);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_destroy_advertiser", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_set_scan_mode
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_set_scan_mode_p
 * @since_tizen                 3.0
 * @author                      SRID(sp.pradhan)
 * @reviewer                    SRID(shobhit.v)
 * @type                        Positive
 * @description                 To test bt_adapter_le_set_scan_mode
 * @scenario                    Call bt_adapter_le_set_scan_mode
 * @apicovered                  bt_adapter_le_set_scan_mode
 * @passcase                    If target API bt_adapter_le_set_scan_mode   return 0
 * @failcase                    If target API bt_adapter_le_set_scan_mode   return non-zero
 * @precondition                Bluetooth must be initialized
 * @postcondition               Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_set_scan_mode_p(void)
{
        START_TEST;
        bt_adapter_le_scan_mode_e SCAN_MODES_NAMES[] =
        {
                BT_ADAPTER_LE_SCAN_MODE_BALANCED,
                BT_ADAPTER_LE_SCAN_MODE_LOW_LATENCY,
                BT_ADAPTER_LE_SCAN_MODE_LOW_ENERGY
        };

        int enum_size = sizeof(SCAN_MODES_NAMES)/sizeof(SCAN_MODES_NAMES[0]);
        int enum_counter = 0;
	int nRet = BT_ERROR_NONE;

        for ( enum_counter=0; enum_counter< enum_size; enum_counter++)
        {
                nRet = bt_adapter_le_set_scan_mode(SCAN_MODES_NAMES[enum_counter]);
		if ( !g_bBluetoothIsLESupported )
		{
			PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_set_scan_mode", BluetoothGetError(nRet));
			return 0;
		}
		PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_set_scan_mode", BluetoothGetError(nRet));
        }
        return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_create and bt_adapter_le_scan_filter_destroy
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_create_destroy_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_create, bt_adapter_le_scan_filter_destroy
 * @scenario                    Call bt_adapter_le_scan_filter_create, then call bt_adapter_le_scan_filter_destroy
 * @apicovered                  bt_adapter_le_scan_filter_create, bt_adapter_le_scan_filter_destroy
 * @passcase                    If target APIs bt_adapter_le_scan_filter_create and bt_adapter_le_scan_filter_destroy   return 0
 * @failcase                    If target APIs bt_adapter_le_scan_filter_create and bt_adapter_le_scan_filter_destroy   return non-zero
 * @precondition                Bluetooth must be initialized
 * @postcondition               Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_scan_filter_create_destroy_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));
	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_register and bt_adapter_le_scan_filter_unregister
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_register_unregister_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_register and bt_adapter_le_scan_filter_unregister
 * @scenario                    Call bt_adapter_le_scan_filter_register, then call bt_adapter_le_scan_filter_unregister
 * @apicovered                  bt_adapter_le_scan_filter_register, bt_adapter_le_scan_filter_unregister
 * @passcase                    If target APIs bt_adapter_le_scan_filter_register and bt_adapter_le_scan_filter_unregister   return 0
 * @failcase                    If target APIs bt_adapter_le_scan_filter_register and bt_adapter_le_scan_filter_unregister   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_register_unregister_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_register(scan_filter);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_register", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_unregister(scan_filter);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_unregister", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_get_scan_result_ibeacon_report and bt_adapter_le_free_ibeacon_report
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_get_scan_result_free_ibeacon_report_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_get_scan_result_ibeacon_report and bt_adapter_le_free_ibeacon_report
 * @scenario                    Call bt_adapter_le_get_scan_result_ibeacon_report and then call bt_adapter_le_free_ibeacon_report
 * @apicovered                  bt_adapter_le_get_scan_result_ibeacon_report, bt_adapter_le_free_ibeacon_report
 * @passcase                    If target APIs bt_adapter_le_get_scan_result_ibeacon_report and bt_adapter_le_free_ibeacon_report   return 0
 * @failcase                    If target APIs bt_adapter_le_get_scan_result_ibeacon_report and bt_adapter_le_free_ibeacon_report   return non-zero
 * @precondition                Bluetooth must be initialized
 *				device_scan_result_info data must be set
 * @postcondition               device_scan_result_info data must be freed
 * 				Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_get_scan_result_free_ibeacon_report_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_adapter_le_device_scan_result_info_s *pszDeviceInfo = NULL;
	bt_adapter_le_ibeacon_scan_result_info_s *pszIbeaconInfo = NULL;

	bt_adapter_le_packet_type_e nAdapterLEPacketType[] =
	{
		BT_ADAPTER_LE_PACKET_ADVERTISING, /**< Advertising packet */
		//BT_ADAPTER_LE_PACKET_SCAN_RESPONSE, /**< Scan response packet */	[NOTE - for this packet type the API is giving error: BT_ERROR_NO_DATA]
	};

        int enum_size = sizeof(nAdapterLEPacketType)/sizeof(nAdapterLEPacketType[0]);
        int enum_counter = 0;


	pszDeviceInfo = (bt_adapter_le_device_scan_result_info_s *)malloc(sizeof(bt_adapter_le_device_scan_result_info_s));
	if(!pszDeviceInfo)
	{
		FPRINTF("[Line : %d][%s] Setting parameters of pszDeviceInfo returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	memset(pszDeviceInfo, 0x00, sizeof(bt_adapter_le_device_scan_result_info_s));

	pszDeviceInfo->remote_address = g_strdup("00:1B:66:01:23:1C");

	if(!pszDeviceInfo->remote_address)
	{
		FPRINTF("[Line : %d][%s] Setting parameters of pszDeviceInfo->remote_address returned NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDeviceInfo->remote_address);	
		FREE_MEMORY(pszDeviceInfo);        
		return 1;
	}

	pszDeviceInfo->address_type = BT_DEVICE_PUBLIC_ADDRESS;
	pszDeviceInfo->rssi = -31;
	pszDeviceInfo->adv_data_len = 31;
	pszDeviceInfo->adv_data = malloc(pszDeviceInfo->adv_data_len);

	if(!pszDeviceInfo->adv_data)
	{
		FPRINTF("[Line : %d][%s] Setting parameters of pszDeviceInfo->adv_data returned NULL\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDeviceInfo->remote_address);
		FREE_MEMORY(pszDeviceInfo->adv_data); 
		FREE_MEMORY(pszDeviceInfo);        
		return 1;
	}

	pszDeviceInfo->adv_data[0] = 28;
	pszDeviceInfo->adv_data[1] = 0xff;

	/* Company ID 0x004C */
	pszDeviceInfo->adv_data[2] = 0x4c;
	pszDeviceInfo->adv_data[3] = 0x00;

	/* UUID */
	pszDeviceInfo->adv_data[4] = 0x01;
	pszDeviceInfo->adv_data[5] = 0x01;
	pszDeviceInfo->adv_data[6] = 0x01;
	pszDeviceInfo->adv_data[7] = 0x01;
	pszDeviceInfo->adv_data[8] = 0x01;
	pszDeviceInfo->adv_data[9] = 0x01;
	pszDeviceInfo->adv_data[10] = 0x01;
	pszDeviceInfo->adv_data[11] = 0x01;
	pszDeviceInfo->adv_data[12] = 0x01;
	pszDeviceInfo->adv_data[13] = 0x01;
	pszDeviceInfo->adv_data[14] = 0x01;
	pszDeviceInfo->adv_data[15] = 0x01;
	pszDeviceInfo->adv_data[16] = 0x01;
	pszDeviceInfo->adv_data[17] = 0x01;
	pszDeviceInfo->adv_data[18] = 0x01;
	pszDeviceInfo->adv_data[19] = 0x01;

	/* Major ID */
	pszDeviceInfo->adv_data[20] = 0x02;
	pszDeviceInfo->adv_data[21] = 0x01;

	/* Minor ID */
	pszDeviceInfo->adv_data[22] = 0x02;
	pszDeviceInfo->adv_data[23] = 0x01;

	/* Power */
	pszDeviceInfo->adv_data[24] = -31;

	if ( !g_bBluetoothIsLESupported )
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_get_scan_result_ibeacon_report can not be called as Bluetooth LE feature is not Supported \\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDeviceInfo->remote_address);
		FREE_MEMORY(pszDeviceInfo->adv_data);
		FREE_MEMORY(pszDeviceInfo);
		//FREE_MEMORY(pszIbeaconInfo);
		return 0;
	}

        for ( enum_counter=0; enum_counter< enum_size; enum_counter++)
        {
		nRet = bt_adapter_le_get_scan_result_ibeacon_report(pszDeviceInfo, nAdapterLEPacketType[enum_counter], &pszIbeaconInfo);
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_get_scan_result_ibeacon_report", BluetoothGetError(nRet), FREE_MEMORY(pszDeviceInfo->remote_address); FREE_MEMORY(pszDeviceInfo->adv_data); FREE_MEMORY(pszDeviceInfo); FREE_MEMORY(pszIbeaconInfo));

		if(!pszIbeaconInfo)
		{
			FPRINTF("[Line : %d][%s] bt_adapter_le_get_scan_result_ibeacon_report returned NULL\\n", __LINE__, API_NAMESPACE);
			FREE_MEMORY(pszDeviceInfo->remote_address);
			FREE_MEMORY(pszDeviceInfo->adv_data);
			FREE_MEMORY(pszDeviceInfo);
			return 1;
		}
		
		nRet = bt_adapter_le_free_ibeacon_report(pszIbeaconInfo);
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_free_ibeacon_report", BluetoothGetError(nRet), FREE_MEMORY(pszDeviceInfo->remote_address); FREE_MEMORY(pszDeviceInfo->adv_data); FREE_MEMORY(pszDeviceInfo);FREE_MEMORY(pszIbeaconInfo));
        }

	FREE_MEMORY(pszDeviceInfo->remote_address);
	FREE_MEMORY(pszDeviceInfo->adv_data);
	FREE_MEMORY(pszDeviceInfo);

	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_unregister_all
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_unregister_all_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_unregister_all
 * @scenario                    Call bt_adapter_le_scan_filter_register, then call bt_adapter_le_scan_filter_unregister_all
 * @apicovered                  bt_adapter_le_scan_filter_unregister_all
 * @passcase                    If target API bt_adapter_le_scan_filter_unregister_all   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_unregister_all   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_unregister_all_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_register(scan_filter);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_register", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_unregister_all();
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_unregister_all", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_type
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_type_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_type
 * @scenario                    Call bt_adapter_le_scan_filter_set_type
 * @apicovered                  bt_adapter_le_scan_filter_set_type
 * @passcase                    If target API bt_adapter_le_scan_filter_set_type   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_type   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_type_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	bt_adapter_le_scan_filter_type_e nAdapterScanFilterType[] = 
	{
		BT_ADAPTER_LE_SCAN_FILTER_TYPE_IBEACON, /**< iBeacon filter type */
		BT_ADAPTER_LE_SCAN_FILTER_TYPE_PROXIMITY_UUID /**< Proximity UUID filter type */
	};

        int enum_size = sizeof(nAdapterScanFilterType)/sizeof(nAdapterScanFilterType[0]);
        int enum_counter = 0;

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);
	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

        for ( enum_counter=0; enum_counter< enum_size; enum_counter++)
        {
		nRet = bt_adapter_le_scan_filter_set_type(scan_filter, nAdapterScanFilterType[enum_counter]);
		PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_type", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));
        }

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));
        return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_manufacturer_data
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_manufacturer_data_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_manufacturer_data
 * @scenario                    Call bt_adapter_le_scan_filter_set_manufacturer_data
 * @apicovered                  bt_adapter_le_scan_filter_set_manufacturer_data
 * @passcase                    If target API bt_adapter_le_scan_filter_set_manufacturer_data   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_manufacturer_data   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_manufacturer_data_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	int manufacturer_id = 117;
	char *pszManufactureData = NULL;
	char manufacture_0[] = {0x0, 0x0, 0x0, 0x0};
	pszManufactureData = manufacture_0;

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_manufacturer_data(scan_filter, manufacturer_id, pszManufactureData, sizeof(manufacture_0));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_manufacturer_data", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_manufacturer_data_with_mask
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_manufacturer_data_with_mask_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_manufacturer_data_with_mask
 * @scenario                    Call bt_adapter_le_scan_filter_set_manufacturer_data_with_mask
 * @apicovered                  bt_adapter_le_scan_filter_set_manufacturer_data_with_mask
 * @passcase                    If target API bt_adapter_le_scan_filter_set_manufacturer_data_with_mask   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_manufacturer_data_with_mask   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_manufacturer_data_with_mask_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;

	int manufacturer_id = 117;
	char *pszManufactureData = NULL;
	char manufacture_0[] = {0x0, 0x0, 0x0, 0x0};
	pszManufactureData = manufacture_0;
	const char *pszManufactureDatamask = "0x04";

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_manufacturer_data_with_mask(scan_filter, manufacturer_id, pszManufactureData, sizeof(manufacture_0), pszManufactureDatamask, strlen(pszManufactureDatamask));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_manufacturer_data_with_mask", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_service_uuid
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_uuid_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_uuid
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_uuid
 * @apicovered                  bt_adapter_le_scan_filter_set_service_uuid
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_uuid   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_uuid   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_uuid_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;
	const char *pszTimeSVCUUID_16 = "1805";
	
	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_uuid(scan_filter, pszTimeSVCUUID_16);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_service_uuid", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_service_uuid_with_mask
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_uuid_with_mask_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_uuid_with_mask
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_uuid_with_mask
 * @apicovered                  bt_adapter_le_scan_filter_set_service_uuid_with_mask
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_uuid_with_mask   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_uuid_with_mask   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_uuid_with_mask_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;
	const char *pszTimeSVCUUID_16 = "1805";
	const char *pszServiceUUIDmask = "0003";

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_uuid_with_mask(scan_filter, pszTimeSVCUUID_16, pszServiceUUIDmask);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_service_uuid_with_mask", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_service_solicitation_uuid
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_solicitation_uuid_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_solicitation_uuid
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_solicitation_uuid
 * @apicovered                  bt_adapter_le_scan_filter_set_service_solicitation_uuid
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_solicitation_uuid   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_solicitation_uuid   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_solicitation_uuid_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;
	const char *pszHeartRateSVCUUID_16 = "180d";

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_solicitation_uuid(scan_filter, pszHeartRateSVCUUID_16);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_service_solicitation_uuid", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To test bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask
 * @apicovered                  bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	bt_scan_filter_h scan_filter = NULL;
	const char *pszHeartRateSVCUUID_16 = "180d";
	const char *pszUUIDMask = "000e";

	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask(scan_filter, pszHeartRateSVCUUID_16, pszUUIDMask);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_service_solicitation_uuid_with_mask", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_set_service_data
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_data_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_data
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_data
 * @apicovered                  bt_adapter_le_scan_filter_set_service_data
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_data   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_data   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_data_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	char service_data[] = {0x01, 0x02, 0x03};
	const char *pszTimeSVCUUID_16 = "1805";
	bt_scan_filter_h scan_filter = NULL;
	
	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_data(scan_filter, pszTimeSVCUUID_16, service_data, sizeof(service_data));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_service_data", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_set_service_data_with_mask
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_service_data_with_mask_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_service_data_with_mask
 * @scenario                    Call bt_adapter_le_scan_filter_set_service_data_with_mask
 * @apicovered                  bt_adapter_le_scan_filter_set_service_data_with_mask
 * @passcase                    If target API bt_adapter_le_scan_filter_set_service_data_with_mask   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_service_data_with_mask   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_service_data_with_mask_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	char service_data[] = {0x01, 0x02, 0x03};
	const char *pszTimeSVCUUID_16 = "1805";
	const char mask[] = {0x04, 0x05, 0x06};

	bt_scan_filter_h scan_filter = NULL;
	
	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_service_data_with_mask(scan_filter, pszTimeSVCUUID_16, service_data, sizeof(service_data), mask, sizeof(mask));
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "ITc_bt_adapter_le_scan_filter_set_service_data_with_mask", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_set_device_name
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_device_name_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_device_name
 * @scenario                    Call bt_adapter_le_scan_filter_set_device_name
 * @apicovered                  bt_adapter_le_scan_filter_set_device_name
 * @passcase                    If target API bt_adapter_le_scan_filter_set_device_name   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_device_name   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_device_name_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	const char *pszDeviceName = "TEST LE ADAPTER";
	bt_scan_filter_h scan_filter = NULL;
	
	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_device_name(scan_filter, pszDeviceName);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_device_name", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));
	return 0;
}


//& purpose: To test bt_adapter_le_scan_filter_set_device_address
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_scan_filter_set_device_address_p
 * @since_tizen                 4.0
 * @author                      SRID(j.abhishek)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To test bt_adapter_le_scan_filter_set_device_address
 * @scenario                    Call bt_adapter_le_scan_filter_set_device_address
 * @apicovered                  bt_adapter_le_scan_filter_set_device_address
 * @passcase                    If target API bt_adapter_le_scan_filter_set_device_address   return 0
 * @failcase                    If target API bt_adapter_le_scan_filter_set_device_address   return non-zero
 * @precondition                Bluetooth must be initialized
 *				Scan filter must be created
 * @postcondition               Bluetooth must be deinitialized, Scan filter must be destroyed
 */
int ITc_bt_adapter_le_scan_filter_set_device_address_p(void)
{
	START_TEST;

	int nRet = BT_ERROR_NONE;
	const char *pszDeviceAddress = "F6:FB:8F:D8:C8:7C";
	bt_scan_filter_h scan_filter = NULL;
	
	nRet = bt_adapter_le_scan_filter_create(&scan_filter);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_create", BluetoothGetError(nRet));

	if(!scan_filter)
	{
		FPRINTF("[Line : %d][%s] bt_adapter_le_scan_filter_create returned NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = bt_adapter_le_scan_filter_set_device_address(scan_filter, pszDeviceAddress);
	PRINT_RESULT_CLEANUP(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_set_device_address", BluetoothGetError(nRet), bt_adapter_le_scan_filter_destroy(scan_filter));

	nRet = bt_adapter_le_scan_filter_destroy(scan_filter);
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_scan_filter_destroy", BluetoothGetError(nRet));

	return 0;
}


//& purpose: To check if LE 2M PHY feature is supported or not.
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_is_2m_phy_supported_p
 * @since_tizen                 5.0
 * @author                      SRID(karanam.s)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To check if LE 2M PHY feature is supported or not
 * @scenario                    Call bt_adapter_le_is_2m_phy_supported_p
 * @apicovered                  bt_adapter_le_is_2m_phy_supported_p
 * @passcase                    If target API bt_adapter_le_is_2m_phy_supported_p   return 0
 * @failcase                    If target API bt_adapter_le_is_2m_phy_supported_p   return non-zero
 * @precondition                Bluetooth must be initialized
 * @postcondition               Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_is_2m_phy_supported_p(void)
{
	START_TEST;

	bool bIsSupported = false;
	bool bBluetoothLE5IsSupported = false;
	if ( TCTCheckSystemInfoFeatureSupported(BLUETOOTH_LE5_FEATURE, API_NAMESPACE) )
	{
		bBluetoothLE5IsSupported = true;
	}

	int nRet = bt_adapter_le_is_2m_phy_supported(&bIsSupported);
	if ( !bBluetoothLE5IsSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_is_2m_phy_supported", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_is_2m_phy_supported", BluetoothGetError(nRet));
	return 0;
}

//& purpose: To check if LE CODED PHY feature is supported or not.
//& type: auto
/**
 * @testcase                    ITc_bt_adapter_le_is_coded_phy_supported_p
 * @since_tizen                 5.0
 * @author                      SRID(karanam.s)
 * @reviewer                    SRID(nibha.sharma)
 * @type                        Positive
 * @description                 To check if LE CODED PHY feature is supported or not
 * @scenario                    Call bt_adapter_le_is_coded_phy_supported
 * @apicovered                  bt_adapter_le_is_coded_phy_supported
 * @passcase                    If target API bt_adapter_le_is_coded_phy_supported   return 0
 * @failcase                    If target API bt_adapter_le_is_coded_phy_supported   return non-zero
 * @precondition                Bluetooth must be initialized
 * @postcondition               Bluetooth must be deinitialized
 */
int ITc_bt_adapter_le_is_coded_phy_supported_p(void)
{
	START_TEST;

	bool bIsSupported = false;
	bool bBluetoothLE5IsSupported = false;
	if ( TCTCheckSystemInfoFeatureSupported(BLUETOOTH_LE5_FEATURE, API_NAMESPACE) )
	{
		bBluetoothLE5IsSupported = true;
	}

	int nRet = bt_adapter_le_is_coded_phy_supported(&bIsSupported);
	if ( !bBluetoothLE5IsSupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_is_coded_phy_supported", BluetoothGetError(nRet));
		return 0;
	}
	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_is_coded_phy_supported", BluetoothGetError(nRet));

	return 0;
}

//& purpose: To check for the LE device discovery is in progress or not.
//& type: auto
/**
* @testcase 			ITc_bt_adapter_le_is_discovering_p
* @since				6.0
* @author				SRID(priya.kohli)
* @reviewer				SRID(shobhit.v)
* @type					positive
* @description			Checks for the LE device discovery is in progress or not.
* @scenario				Checks for the LE device discovery status; is in progress or not.
* @apicovered			bt_adapter_le_is_discovering
* @passcase				When bt_adapter_le_is_discovering is successful
* @failcase				If target APIs or any pre-condition fails
* @precondition			Bluetooth must be initialized
* @postcondition		Bluetooth must be de-initialized
*/
int ITc_bt_adapter_le_is_discovering_p(void)
{
	START_TEST;

	bool bIsDiscovery = FALSE;
	int nRet = bt_adapter_le_is_discovering(&bIsDiscovery);

	if ( !g_bBluetoothIsLESupported )
	{
		PRINT_RESULT(BT_ERROR_NOT_SUPPORTED, nRet, "bt_adapter_le_is_discovering", BluetoothGetError(nRet));
		return 0;
	}

	PRINT_RESULT(BT_ERROR_NONE, nRet, "bt_adapter_le_is_discovering", BluetoothGetError(nRet));

	return 0;
}
/** @} */
/** @} */
