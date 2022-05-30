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
#include "ITs-telephony-common.h"

/** @addtogroup itc-telephony
*  @ingroup itc
*  @{
*/

extern telephony_handle_list_s g_stTelephonyHandleList;
extern telephony_h g_pstTelephonySIMHandle;

/**
* @function 		TelephonyGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			State string
*/
char *TelephonyGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case TELEPHONY_ERROR_NONE:					szErrorVal = "TELEPHONY_ERROR_NONE";					break;
	case TELEPHONY_ERROR_OUT_OF_MEMORY:			szErrorVal = "TELEPHONY_ERROR_OUT_OF_MEMORY";			break;
	case TELEPHONY_ERROR_INVALID_PARAMETER:		szErrorVal = "TELEPHONY_ERROR_INVALID_PARAMETER";		break;
	case TELEPHONY_ERROR_PERMISSION_DENIED:		szErrorVal = "TELEPHONY_ERROR_PERMISSION_DENIED";		break;
	case TELEPHONY_ERROR_NOT_SUPPORTED:			szErrorVal = "TELEPHONY_ERROR_NOT_SUPPORTED";			break;
	case TELEPHONY_ERROR_OPERATION_FAILED:		szErrorVal = "TELEPHONY_ERROR_OPERATION_FAILED";		break;
	case TELEPHONY_ERROR_SIM_NOT_AVAILABLE:		szErrorVal = "TELEPHONY_ERROR_SIM_NOT_AVAILABLE";		break;
	default:									szErrorVal = "Unknown State";							break;
	}
	return szErrorVal;
}

/**
* @function 		ConnectionGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ConnectionGetError(connection_error_e nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
	case CONNECTION_ERROR_NONE : 							szErrorVal = "CONNECTION_ERROR_NONE"; 							break;/**< Successful */
	case CONNECTION_ERROR_INVALID_PARAMETER : 				szErrorVal = "CONNECTION_ERROR_INVALID_PARAMETER"; 				break;/**< Invalid parameter */
	case CONNECTION_ERROR_OUT_OF_MEMORY: 					szErrorVal = "CONNECTION_ERROR_OUT_OF_MEMORY"; 					break;/**< Out of memory error */
	case CONNECTION_ERROR_INVALID_OPERATION : 				szErrorVal = "CONNECTION_ERROR_INVALID_OPERATION"; 				break;/**< Invalid Operation */
	case CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED : 	szErrorVal = "CONNECTION_ERROR_ADDRESS_FAMILY_NOT_SUPPORTED"; 	break;/**< Address family not supported */
	case CONNECTION_ERROR_OPERATION_FAILED : 				szErrorVal = "CONNECTION_ERROR_OPERATION_FAILED"; 				break;/**< Operation failed */
	case CONNECTION_ERROR_ITERATOR_END : 					szErrorVal = "CONNECTION_ERROR_ITERATOR_END"; 					break;/**< End of iteration */
	case CONNECTION_ERROR_NO_CONNECTION : 					szErrorVal = "CONNECTION_ERROR_NO_CONNECTION"; 					break;/**< There is no connection */
	case CONNECTION_ERROR_NOW_IN_PROGRESS : 				szErrorVal = "CONNECTION_ERROR_NOW_IN_PROGRESS"; 				break;/** Now in progress */
	case CONNECTION_ERROR_ALREADY_EXISTS : 					szErrorVal = "CONNECTION_ERROR_ALREADY_EXISTS"; 				break;/**< Already exists */
	case CONNECTION_ERROR_OPERATION_ABORTED : 				szErrorVal = "CONNECTION_ERROR_OPERATION_ABORTED"; 				break;/**< Operation is aborted */
	case CONNECTION_ERROR_DHCP_FAILED : 					szErrorVal = "CONNECTION_ERROR_DHCP_FAILED"; 					break;/**< DHCP failed  */
	case CONNECTION_ERROR_INVALID_KEY : 					szErrorVal = "CONNECTION_ERROR_INVALID_KEY"; 					break;/**< Invalid key  */
	case CONNECTION_ERROR_NO_REPLY : 						szErrorVal = "CONNECTION_ERROR_NO_REPLY"; 						break;/**< No reply */
	case CONNECTION_ERROR_PERMISSION_DENIED : 				szErrorVal = "CONNECTION_ERROR_PERMISSION_DENIED"; 				break;/**< Permission denied */
	case CONNECTION_ERROR_NOT_SUPPORTED : 					szErrorVal = "CONNECTION_ERROR_NOT_SUPPORTED"; 					break;/**< Not supported */
	case CONNECTION_ERROR_ALREADY_INITIALIZED : 			szErrorVal = "CONNECTION_ERROR_ALREADY_INITIALIZED"; 			break;/**< Already initialized */
	case CONNECTION_ERROR_NOT_INITIALIZED : 				szErrorVal = "CONNECTION_ERROR_NOT_INITIALIZED"; 				break;/**< Not initialized */
	default : 												szErrorVal = "Unknown Error"; 									break;
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetServiceState
* @description	 	Maps enums values to string values
* @parameter		eRet : service state
* @return 			State string
*/
char *TelephonyGetServiceState(telephony_network_service_state_e eRet)
{
	char *szErrorVal = "Unknown State";
	switch ( eRet )
	{
	case TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE:		szErrorVal = "TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE";			break;
	case TELEPHONY_NETWORK_SERVICE_STATE_OUT_OF_SERVICE:	szErrorVal = "TELEPHONY_NETWORK_SERVICE_STATE_OUT_OF_SERVICE";		break;
	case TELEPHONY_NETWORK_SERVICE_STATE_EMERGENCY_ONLY:	szErrorVal = "TELEPHONY_NETWORK_SERVICE_STATE_EMERGENCY_ONLY";		break;
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetSimState
* @description	 	Maps enums values to string values
* @parameter		eRet : sim state
* @return 			State string
*/
char *TelephonyGetSimState(telephony_sim_state_e eRet)
{
	char *szErrorVal = "Unknown State";
	switch ( eRet )
	{
	case TELEPHONY_SIM_STATE_UNAVAILABLE:			szErrorVal = "TELEPHONY_SIM_STATE_UNAVAILABLE";			break;
	case TELEPHONY_SIM_STATE_LOCKED:				szErrorVal = "TELEPHONY_SIM_STATE_LOCKED";				break;
	case TELEPHONY_SIM_STATE_AVAILABLE:				szErrorVal = "TELEPHONY_SIM_STATE_AVAILABLE";			break;
	case TELEPHONY_SIM_STATE_UNKNOWN:				szErrorVal = "TELEPHONY_SIM_STATE_UNKNOWN";				break;
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetSimState
* @description	 	Maps enums values to string values
* @parameter		eRet : sim state
* @return 			State string
*/
char *TelephonyGetSimLockState(telephony_sim_lock_state_e eRet)
{
	char *szErrorVal = "Unknown Lock State";
	switch ( eRet )
	{
	case TELEPHONY_SIM_LOCK_STATE_UNKNOWN:			szErrorVal = "TELEPHONY_SIM_LOCK_STATE_UNKNOWN";			break;
	case TELEPHONY_SIM_LOCK_STATE_PIN_REQUIRED:				szErrorVal = "TELEPHONY_SIM_LOCK_STATE_PIN_REQUIRED";				break;
	case TELEPHONY_SIM_LOCK_STATE_PUK_REQUIRED:				szErrorVal = "TELEPHONY_SIM_LOCK_STATE_PUK_REQUIRED";			break;
	case TELEPHONY_SIM_LOCK_STATE_PERM_LOCKED:				szErrorVal = "TELEPHONY_SIM_LOCK_STATE_PERM_LOCKED";				break;
	case TELEPHONY_SIM_LOCK_STATE_NCK_REQUIRED:				szErrorVal = "TELEPHONY_SIM_LOCK_STATE_NCK_REQUIRED";				break;
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetRSSIValue
* @description	 	Maps enums values to string values
* @parameter		eRet : rssi state
* @return 			string to rssi strength
*/
char *TelephonyGetRSSIValue(telephony_network_rssi_e eRet)
{
	char *szErrorVal = "Unknown Value";
	switch ( eRet )
	{
	case TELEPHONY_NETWORK_RSSI_0:				szErrorVal = "TELEPHONY_NETWORK_RSSI_0";				break;
	case TELEPHONY_NETWORK_RSSI_1:				szErrorVal = "TELEPHONY_NETWORK_RSSI_1";				break;
	case TELEPHONY_NETWORK_RSSI_2:				szErrorVal = "TELEPHONY_NETWORK_RSSI_2";				break;
	case TELEPHONY_NETWORK_RSSI_3:				szErrorVal = "TELEPHONY_NETWORK_RSSI_3";				break;
	case TELEPHONY_NETWORK_RSSI_4:				szErrorVal = "TELEPHONY_NETWORK_RSSI_4";				break;
	case TELEPHONY_NETWORK_RSSI_5:				szErrorVal = "TELEPHONY_NETWORK_RSSI_5";				break;
	case TELEPHONY_NETWORK_RSSI_6:				szErrorVal = "TELEPHONY_NETWORK_RSSI_6";				break;
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetNetworkType
* @description	 	Maps enums values to string values
* @parameter		eRet : network service type
* @return 			string to network service type
*/
char *TelephonyGetNetworkType(telephony_network_type_e eRet)
{
	char *szErrorVal = "Unknown Type";
	switch ( eRet )
	{
	case TELEPHONY_NETWORK_TYPE_UNKNOWN:			szErrorVal = "TELEPHONY_NETWORK_TYPE_UNKNOWN";			break;
	case TELEPHONY_NETWORK_TYPE_GSM:				szErrorVal = "TELEPHONY_NETWORK_TYPE_GSM";				break;
	case TELEPHONY_NETWORK_TYPE_GPRS:				szErrorVal = "TELEPHONY_NETWORK_TYPE_GPRS";				break;
	case TELEPHONY_NETWORK_TYPE_EDGE:				szErrorVal = "TELEPHONY_NETWORK_TYPE_EDGE";				break;
	case TELEPHONY_NETWORK_TYPE_UMTS:				szErrorVal = "TELEPHONY_NETWORK_TYPE_UMTS";				break;
	case TELEPHONY_NETWORK_TYPE_HSDPA:				szErrorVal = "TELEPHONY_NETWORK_TYPE_HSDPA";			break;
	case TELEPHONY_NETWORK_TYPE_LTE:				szErrorVal = "TELEPHONY_NETWORK_TYPE_LTE";				break;
	case TELEPHONY_NETWORK_TYPE_IS95A:           	szErrorVal = "TELEPHONY_NETWORK_TYPE_IS95A";			break;/**< IS95A network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_IS95B:          	szErrorVal = "TELEPHONY_NETWORK_TYPE_IS95B";			break;/**< IS95B network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_CDMA_1X:        	szErrorVal = "TELEPHONY_NETWORK_TYPE_CDMA_1X";			break;/**< CDMA 1x network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_EVDO_REV_0:     	szErrorVal = "TELEPHONY_NETWORK_TYPE_EVDO_REV_0";		break;/**< EVDO revision 0 network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_EVDO_REV_A:     	szErrorVal = "TELEPHONY_NETWORK_TYPE_EVDO_REV_A";		break;/**< EVDO revision A network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_EVDO_REV_B:     	szErrorVal = "TELEPHONY_NETWORK_TYPE_EVDO_REV_B";		break;/**< EVDO revision B network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_EVDV:      			szErrorVal = "TELEPHONY_NETWORK_TYPE_EVDV";				break;/**< EVDV network type (Since: 3.0) */
    case TELEPHONY_NETWORK_TYPE_EHRPD:         		szErrorVal = "TELEPHONY_NETWORK_TYPE_EHRPD";			break; /**< EHRPD network type (Since: 3.0) */
	}
	return szErrorVal;
}

/**
* @function 		TelephonyGetNetworkSelMode (Since: 3.0)
* @description	 	Maps enums values to string values
* @parameter		eRet : network selection mode
* @return 			string to network selection mode
*/
char *TelephonyGetNetworkSelMode(telephony_network_selection_mode_e eRet)
{
	char *szErrorVal = "Unknown Type";
	switch ( eRet )
	{

	case TELEPHONY_NETWORK_SELECTION_MODE_AUTOMATIC:  	szErrorVal = "TELEPHONY_NETWORK_SELECTION_MODE_AUTOMATIC";		break;   /**< Automatic mode */
    case TELEPHONY_NETWORK_SELECTION_MODE_MANUAL:     	szErrorVal = "TELEPHONY_NETWORK_SELECTION_MODE_MANUAL";			break;    /**< Manual mode */
	}
	return szErrorVal;
}

/**
* @function            TelephonyGetState
* @description        Maps enums values to string values
* @parameter         eRet : telephony state
* @return               string to telephony state
*/
char *TelephonyGetState(telephony_state_e eRet)
{
	char *stateVal = "Unknown State";
	switch ( eRet )
	{
	case TELEPHONY_STATE_NOT_READY:    stateVal = "TELEPHONY_STATE_NOT_READY";    break;
	case TELEPHONY_STATE_READY:        stateVal = "TELEPHONY_STATE_READY";        break;
	}
	return stateVal;
}

/**
* @function 		TelephonyGetSimHandle
* @description	 	Gets the correct sim handle in case of dual sim device
* @parameter		nSlotCount : number of sim slots in the device
* @return 			true if it gets a handle, false if no handle is obtained
*/
bool TelephonyGetSimHandle(int nSlotCount)
{
	bool bSlotError = false;
	int nRet = 0;
	telephony_network_service_state_e eNetworkServiceState;
	switch ( nSlotCount )
	{
	case 0 : FPRINTF("[Line : %d][%s] telephony_init failed, error returned = list returned is empty \\n", __LINE__, API_NAMESPACE);
		break;

	case 1 : nRet = telephony_network_get_service_state(g_stTelephonyHandleList.handle[0], &eNetworkServiceState);
		if ( nRet == TELEPHONY_ERROR_NONE )
		{
			if ( eNetworkServiceState == TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE )
			{
				g_pstTelephonySIMHandle = g_stTelephonyHandleList.handle[0];
				bSlotError = true;
			}
			else
			{
				FPRINTF("[Line : %d][%s] telephony_network_get_service_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetServiceState(eNetworkServiceState));
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] telephony_network_get_service_state failed, error returned = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetError(nRet));
		}
		break;

	case 2 : nRet = telephony_network_get_service_state(g_stTelephonyHandleList.handle[0], &eNetworkServiceState);
		if ( nRet == TELEPHONY_ERROR_NONE )
		{
			if ( eNetworkServiceState == TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE )
			{
				g_pstTelephonySIMHandle = g_stTelephonyHandleList.handle[0];
				bSlotError = true;
				break;
			}
			else
			{
				FPRINTF("[Line : %d][%s] telephony_network_get_service_state for primary SIM slot returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetServiceState(eNetworkServiceState));
				FPRINTF("[Line : %d][%s] checking for secondary slot \\n", __LINE__, API_NAMESPACE);
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] telephony_network_get_service_state failed for primary SIM slot, error returned = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetError(nRet));
			FPRINTF("[Line : %d][%s] checking for secondary slot \\n", __LINE__, API_NAMESPACE);
		}
		sleep(1);
		nRet = telephony_network_get_service_state(g_stTelephonyHandleList.handle[1], &eNetworkServiceState);
		if ( nRet == TELEPHONY_ERROR_NONE )
		{
			if ( eNetworkServiceState == TELEPHONY_NETWORK_SERVICE_STATE_IN_SERVICE )
			{
				g_pstTelephonySIMHandle = g_stTelephonyHandleList.handle[1];
				bSlotError = true;
				break;
			}
			else
			{
				FPRINTF("[Line : %d][%s] telephony_network_get_service_state for secondary slot returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetServiceState(eNetworkServiceState));
			}
		}
		else
		{
			FPRINTF("[Line : %d][%s] telephony_network_get_service_state failed for secondary slot, error returned = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetError(nRet));
		}
		break;
	}
	return bSlotError;
}
/** @} */
