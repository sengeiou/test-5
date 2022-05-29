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
#include "ITs-iotcon-common.h"

/** @addtogroup itc-iotcon
*  @ingroup itc
*  @{
*/

//Add helper function definitions here

/**
* @function 		IotConGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* IotConGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case IOTCON_ERROR_NONE:					szErrorVal = "IOTCON_ERROR_NONE";					break;
		case IOTCON_ERROR_IO_ERROR:   			szErrorVal = "IOTCON_ERROR_IO_ERROR";				break;
		case IOTCON_ERROR_OUT_OF_MEMORY:       	szErrorVal = "IOTCON_ERROR_OUT_OF_MEMORY";			break;
		case IOTCON_ERROR_PERMISSION_DENIED:   	szErrorVal = "IOTCON_ERROR_PERMISSION_DENIED";		break;
		case IOTCON_ERROR_NOT_SUPPORTED:       	szErrorVal = "IOTCON_ERROR_NOT_SUPPORTED";			break;
		case IOTCON_ERROR_INVALID_PARAMETER: 	szErrorVal = "IOTCON_ERROR_INVALID_PARAMETER";		break;
		case IOTCON_ERROR_NO_DATA: 				szErrorVal = "IOTCON_ERROR_NO_DATA";				break;
		case IOTCON_ERROR_TIMEOUT:   			szErrorVal = "IOTCON_ERROR_TIMEOUT";				break;
		case IOTCON_ERROR_IOTIVITY:   			szErrorVal = "IOTCON_ERROR_IOTIVITY";				break;
		case IOTCON_ERROR_REPRESENTATION:	    szErrorVal = "IOTCON_ERROR_REPRESENTATION";			break;
		case IOTCON_ERROR_INVALID_TYPE:         szErrorVal = "IOTCON_ERROR_INVALID_TYPE";			break;
		case IOTCON_ERROR_ALREADY:				szErrorVal = "IOTCON_ERROR_ALREADY";				break;
		case IOTCON_ERROR_SYSTEM:           	szErrorVal = "IOTCON_ERROR_SYSTEM";					break;
		default : 					           	szErrorVal = "Unknown Error";						break;
	}
	return szErrorVal;
}

int icitc_send_ok_response(iotcon_request_h request)
{

	int ret;
	iotcon_response_h response = NULL;
	iotcon_options_h options = NULL;
	iotcon_representation_h repr = NULL;

	ret = iotcon_response_create(request, &response);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_response_create() Fail(%d)", ret);
		return 1;
	}

	ret = iotcon_options_create(&options);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_options_create() Fail(%d)", ret);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_options_add(options, 2048, "1");
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_options_add() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_set_result(response, IOTCON_RESPONSE_OK);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_response_set_result() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_set_options(response, options);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_response_send() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

/*ret = icutc_create_representation(&repr);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("icutc_create_representation() Fail(%d)", ret);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}
*/
	ret = iotcon_response_set_representation(response, repr);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_response_set_representation() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	ret = iotcon_response_send(response);
	if (IOTCON_ERROR_NONE != ret) {
		FPRINTF("iotcon_response_send() Fail(%d)", ret);
		iotcon_representation_destroy(repr);
		iotcon_options_destroy(options);
		iotcon_response_destroy(response);
		return 1;
	}

	iotcon_representation_destroy(repr);
	iotcon_options_destroy(options);
	iotcon_response_destroy(response);

	return 0;
}
/**
 * @function 		TimeoutFunction
 * @description	 	Called if some callback is not invoked for a particular timeout
 * @parameter		gpointer data
 * @return 			gboolean
 */
/*gboolean TimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Timeout after %d seconds\\n", __LINE__, API_NAMESPACE, TIMEOUT_CB/1000);
	QuitGmainLoop();
	return false;
}
*/

/**
* @function 		IterateGmainLoop
* @description	 	Called to wait
* @parameter		NA
* @return 			NA
*/
void IterateGmainLoop(void)
{
	if(g_CallBackHit == false)
	{
		g_pMainLoop = g_main_loop_new(NULL, false);
		g_nTimeoutId = g_timeout_add(TIMEOUT_CB, TimeoutFunction, NULL);
		g_main_loop_run(g_pMainLoop);

		g_source_remove(g_nTimeoutId);
		g_nTimeoutId = 0;

		g_main_loop_unref(g_pMainLoop);
		g_pMainLoop = NULL;
	}
}

/**
* @function 		QuitGmainLoop
* @description	 	Called to quit
* @parameter		NA
* @return 			NA
*/
void QuitGmainLoop(void)
{
	if(g_pMainLoop)
	{
		g_main_loop_quit(g_pMainLoop);
	}
}


/**
* @function 		TimeoutFunction
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	g_main_loop_quit((GMainLoop *)data);
	return false;
}

/**
 * @function 		IotconDestroyLiteResource
 * @description	 	Destroy lite resource iotcon
 * @parameter		NA
 * @return 			NA
 */
void IotconDestroyLiteResource(void)
{
	if (g_hLiteLightResource) {
		int nRet=iotcon_lite_resource_destroy(g_hLiteLightResource);
        if (IOTCON_ERROR_NONE != nRet)
        {
            FPRINTF("[Line : %d][%s] iotcon_resource_destroy fail  error returned : %s\\n", __LINE__, API_NAMESPACE,IotConGetError(nRet));
            return;
        }
		g_hLiteLightResource = NULL;
	}
	return;
}

/**
 * @function 		IotconCreateLiteResource
 * @description	 	Creates lite resource iotcon
 * @parameter		NA
 * @return 			NA
 */
int IotconCreateLiteResource(void)
{
	iotcon_attributes_h state = NULL;
	iotcon_resource_types_h light_types = NULL;

	IotconDestroyLiteResource();

	int nRet = iotcon_resource_types_create(&light_types);
	PRINT_RESULT(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_create", IotConGetError(nRet));
	if(light_types==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_resource_types_create fail light_type is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	nRet = iotcon_resource_types_add(light_types, "core.light");
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_types_add", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));

	nRet = iotcon_attributes_create(&state);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_create", IotConGetError(nRet),iotcon_resource_types_destroy(light_types));
	if(state==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_attributes_create fail states is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}
		//SHILPA
	//nRet = iotcon_attributes_add_int(state, "brightness", ++g_nBrightness);
	 nRet = iotcon_attributes_add_bool(state, "opened", true);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_attributes_add_int", IotConGetError(nRet),iotcon_attributes_destroy(state);iotcon_resource_types_destroy(light_types));

	/* register door resource */
	//nRet = iotcon_lite_resource_create("/a/light", light_types,
			//(IOTCON_INTERFACE_DEFAULT | IOTCON_INTERFACE_BATCH), state, Iotcon_door_attributes_changed_cb_p, NULL, &g_hLiteLightResource);

	//iotcon_resource_interfaces_h ifaces;

	//nRet = iotcon_resource_interfaces_add(ifaces, IOTCON_INTERFACE_BATCH);
	//PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_resource_interfaces_add", IotConGetError(nRet),iotcon_attributes_destroy(state);iotcon_resource_types_destroy(light_types));

	//nRet = iotcon_lite_resource_create("/a/light", light_types,1, state, Iotcon_door_attributes_changed_cb_p, NULL, &g_hLiteLightResource);
	//SHILPA
	nRet = iotcon_lite_resource_create("/a/light", light_types,1, state, NULL, NULL, &g_hLiteLightResource);
	PRINT_RESULT_CLEANUP(IOTCON_ERROR_NONE, nRet, "iotcon_lite_resource_create", IotConGetError(nRet),iotcon_attributes_destroy(state);iotcon_resource_types_destroy(light_types));

	if(g_hLiteLightResource==NULL)
	{
		FPRINTF("[Line : %d][%s] iotcon_lite_resource_create fail g_hLiteLightResource is NULL error returned : \\n", __LINE__, API_NAMESPACE);
		iotcon_attributes_destroy(state);
		iotcon_resource_types_destroy(light_types);
		return 1;
	}

	iotcon_attributes_destroy(state);
	iotcon_resource_types_destroy(light_types);

	return 0;
}

int ic_get_svr_db_path(char **path)
{
	char file_path[PATH_MAX] = {0};
	char pszValue[CONFIG_VALUE_LEN_MAX] = {0,};
	const char *svr_db_file = "svr_db.dat";

	if (false == GetValueForTCTSetting("DEVICE_USER_30", pszValue, API_NAMESPACE)) {
		PRINT_UTC_LOG("[Line : %d][%s] GetValueForTCTSetting returned error for 'DEVICE_SUITE_TARGET_30'\\n", __LINE__, API_NAMESPACE);
		return -1;
	}

	PRINT_UTC_LOG("[Line : %d][%s] 'DEVICE_USER_30' Values Received = %s\\n",
			__LINE__, API_NAMESPACE,  pszValue);

	snprintf(file_path, sizeof(file_path), "%s/apps_rw/native-iotcon-itc/data/%s", pszValue,
			svr_db_file);

	*path = strdup(file_path);

	return 0;
}

/**
 * @function 		icitc_get_client_ipv4_address
 * @description	 	Get my device's IPv4 address and set to global variable
 * @parameter		NA
 * @return 			NA
 */
void icitc_get_client_ipv4_address(void)
{
	g_ipv4_address = NULL;
	g_conn_h = NULL;

	g_bFeatureWifi = TCTCheckSystemInfoFeatureSupported(WIFI_FEATURE, API_NAMESPACE);
	g_bFeatureEthernet = TCTCheckSystemInfoFeatureSupported(ETHERNET_FEATURE, API_NAMESPACE);
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] g_bFeatureWifi(%d), g_bFeatureEthernet(%d)", __FUNCTION__, __LINE__, g_bFeatureWifi, g_bFeatureEthernet);

	if ((g_bFeatureWifi == true) || (g_bFeatureEthernet == true)) {
		int nRet = 0;

		nRet = connection_create(&g_conn_h);
		if (nRet != CONNECTION_ERROR_NONE) {
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] (1/3) connection_create() FAIL(nRet = 0x%x)", __FUNCTION__, __LINE__, nRet);
			return;
		}

		nRet = connection_get_ip_address(g_conn_h, CONNECTION_ADDRESS_FAMILY_IPV4, &g_ipv4_address);
		if (nRet != CONNECTION_ERROR_NONE) {
			dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] (2/3) connection_get_ip_address() FAIL(nRet = 0x%x)", __FUNCTION__, __LINE__, nRet);
		} else {
			dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] g_ipv4_address(%s)", __FUNCTION__, __LINE__, g_ipv4_address);
		}

		if (g_conn_h != NULL) {
			nRet = connection_destroy(g_conn_h);
			if (nRet != CONNECTION_ERROR_NONE) {
				dlog_print(DLOG_ERROR, "NativeTCT", "[%s:%d] (3/3) connection_destroy() FAIL(nRet = 0x%x)", __FUNCTION__, __LINE__, nRet);
				return;
			}
		}
	} else {
		dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] Wi-Fi and Ethernet are both NOT SUPPORTED", __FUNCTION__, __LINE__);
	}
}

/**
 * @function 		icitc_free_client_ipv4_address
 * @description	 	Free IPv4 address global variable
 * @parameter		NA
 * @return 			NA
 */
void icitc_free_client_ipv4_address(void)
{
	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] g_free() g_ipv4_address(%s)", __FUNCTION__, __LINE__, g_ipv4_address);

	if (g_ipv4_address != NULL) {
		g_free(g_ipv4_address);
	}

	dlog_print(DLOG_INFO, "NativeTCT", "[%s:%d] g_free() g_ipv4_address done", __FUNCTION__, __LINE__);
}

/** @} */
