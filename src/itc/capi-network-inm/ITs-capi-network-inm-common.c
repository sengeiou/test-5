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
#include "ITs-capi-network-inm-common.h"

/** @addtogroup itc-dlog
*  @ingroup itc
*  @{
*/

//Add helper function definitions here
char* InmGetError(int error)
{
	char *pszErrorValue = NULL;
	switch (error) {
	case INM_ERROR_NONE:
		pszErrorValue = "INM_ERROR_NONE";
		break;
	case INM_ERROR_NOT_PERMITTED:
		pszErrorValue = "INM_ERROR_NOT_PERMITTED";
		break;
	case INM_ERROR_OUT_OF_MEMORY:
		pszErrorValue = "INM_ERROR_OUT_OF_MEMORY";
		break;
	case INM_ERROR_PERMISSION_DENIED:
		pszErrorValue = "INM_ERROR_PERMISSION_DENIED";
		break;
	case INM_ERROR_RESOURCE_BUSY:
		pszErrorValue = "INM_ERROR_RESOURCE_BUSY";
		break;
	case INM_ERROR_INVALID_PARAMETER:
		pszErrorValue = "INM_ERROR_INVALID_PARAMETER";
		break;
	case INM_ERROR_CONNECTION_TIME_OUT:
		pszErrorValue = "INM_ERROR_CONNECTION_TIME_OUT";
		break;
	case INM_ERROR_NOW_IN_PROGRESS:
		pszErrorValue = "INM_ERROR_NOW_IN_PROGRESS";
		break;
	case INM_ERROR_NOT_SUPPORTED:
		pszErrorValue = "INM_ERROR_NOT_SUPPORTED";
		break;
	case INM_ERROR_NOT_INITIALIZED:
		pszErrorValue = "INM_ERROR_NOT_INITIALIZED";
		break;
	case INM_ERROR_ALREADY_INITIALIZED:
		pszErrorValue = "INM_ERROR_ALREADY_INITIALIZED";
		break;
	case INM_ERROR_OPERATION_FAILED:
		pszErrorValue = "INM_ERROR_OPERATION_FAILED";
		break;
	default:
		pszErrorValue = "Unknown Error";
		break;
	}
	return pszErrorValue;
}

char* InmGetDisconnectReason(int error)
{
	char *pszDisconnectReason = NULL;
	switch (error) {
	case INM_WIFI_REASON_LOCAL_GENERATE_FROM_USER:
		pszDisconnectReason = "INM_WIFI_REASON_LOCAL_GENERATE_FROM_USER";
		break;
	case INM_WIFI_REASON_UNSPECIFIED:
		pszDisconnectReason = "INM_WIFI_REASON_UNSPECIFIED";
		break;
	case INM_WIFI_REASON_PREV_AUTH_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_PREV_AUTH_NOT_VALID";
		break;
	case INM_WIFI_REASON_DEAUTH_LEAVING:
		pszDisconnectReason = "INM_WIFI_REASON_DEAUTH_LEAVING";
		break;
	case INM_WIFI_REASON_DISASSOC_DUE_TO_INACTIVITY:
		pszDisconnectReason = "INM_WIFI_REASON_DISASSOC_DUE_TO_INACTIVITY";
		break;
	case INM_WIFI_REASON_DISASSOC_AP_BUSY:
		pszDisconnectReason = "INM_WIFI_REASON_DISASSOC_AP_BUSY";
		break;
	case INM_WIFI_REASON_CLASS2_FRAME_FROM_NONAUTH_STA:
		pszDisconnectReason = "INM_WIFI_REASON_CLASS2_FRAME_FROM_NONAUTH_STA";
		break;
	case INM_WIFI_REASON_CLASS3_FRAME_FROM_NONASSOC_STA:
		pszDisconnectReason = "INM_WIFI_REASON_CLASS3_FRAME_FROM_NONASSOC_STA";
		break;
	case INM_WIFI_REASON_DISASSOC_STA_HAS_LEFT:
		pszDisconnectReason = "INM_WIFI_REASON_DISASSOC_STA_HAS_LEFT";
		break;
	case INM_WIFI_REASON_STA_REQ_ASSOC_WITHOUT_AUTH:
		pszDisconnectReason = "INM_WIFI_REASON_STA_REQ_ASSOC_WITHOUT_AUTH";
		break;
	case INM_WIFI_REASON_PWR_CAPABILITY_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_PWR_CAPABILITY_NOT_VALID";
		break;
	case INM_WIFI_REASON_SUPPORTED_CHANNEL_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_SUPPORTED_CHANNEL_NOT_VALID";
		break;
	case INM_WIFI_REASON_INVALID_IE:
		pszDisconnectReason = "INM_WIFI_REASON_INVALID_IE";
		break;
	case INM_WIFI_REASON_MICHAEL_MIC_FAILURE:
		pszDisconnectReason = "INM_WIFI_REASON_MICHAEL_MIC_FAILURE";
		break;
	case INM_WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT:
		pszDisconnectReason = "INM_WIFI_REASON_4WAY_HANDSHAKE_TIMEOUT";
		break;
	case INM_WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT:
		pszDisconnectReason = "INM_WIFI_REASON_GROUP_KEY_UPDATE_TIMEOUT";
		break;
	case INM_WIFI_REASON_IE_IN_4WAY_DIFFERS:
		pszDisconnectReason = "INM_WIFI_REASON_IE_IN_4WAY_DIFFERS";
		break;
	case INM_WIFI_REASON_GROUP_CIPHER_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_GROUP_CIPHER_NOT_VALID";
		break;
	case INM_WIFI_REASON_PAIRWISE_CIPHER_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_PAIRWISE_CIPHER_NOT_VALID";
		break;
	case INM_WIFI_REASON_AKMP_NOT_VALID:
		pszDisconnectReason = "INM_WIFI_REASON_AKMP_NOT_VALID";
		break;
	case INM_WIFI_REASON_UNSUPPORTED_RSN_IE_VERSION:
		pszDisconnectReason = "INM_WIFI_REASON_UNSUPPORTED_RSN_IE_VERSION";
		break;
	case INM_WIFI_REASON_INVALID_RSN_IE_CAPAB:
		pszDisconnectReason = "INM_WIFI_REASON_INVALID_RSN_IE_CAPAB";
		break;
	case INM_WIFI_REASON_IEEE_802_1X_AUTH_FAILED:
		pszDisconnectReason = "INM_WIFI_REASON_IEEE_802_1X_AUTH_FAILED";
		break;
	case INM_WIFI_REASON_CIPHER_SUITE_REJECTED:
		pszDisconnectReason = "INM_WIFI_REASON_CIPHER_SUITE_REJECTED";
		break;
	case INM_WIFI_REASON_TDLS_TEARDOWN_UNREACHABLE:
		pszDisconnectReason = "INM_WIFI_REASON_TDLS_TEARDOWN_UNREACHABLE";
		break;
	case INM_WIFI_REASON_TDLS_TEARDOWN_UNSPECIFIED:
		pszDisconnectReason = "INM_WIFI_REASON_TDLS_TEARDOWN_UNSPECIFIED";
		break;
	case INM_WIFI_REASON_DISASSOC_LOW_ACK:
		pszDisconnectReason = "INM_WIFI_REASON_DISASSOC_LOW_ACK";
		break;
	case INM_WIFI_REASON_MESH_PEERING_CANCELLED:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_PEERING_CANCELLED";
		break;
	case INM_WIFI_REASON_MESH_MAX_PEERS:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_MAX_PEERS";
		break;
	case INM_WIFI_REASON_MESH_CONFIG_POLICY_VIOLATION:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_CONFIG_POLICY_VIOLATION";
		break;
	case INM_WIFI_REASON_MESH_CLOSE_RCVD:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_CLOSE_RCVD";
		break;
	case INM_WIFI_REASON_MESH_MAX_RETRIES:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_MAX_RETRIES";
		break;
	case INM_WIFI_REASON_MESH_CONFIRM_TIMEOUT:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_CONFIRM_TIMEOUT";
		break;
	case INM_WIFI_REASON_MESH_INVALID_GTK:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_INVALID_GTK";
		break;
	case INM_WIFI_REASON_MESH_INCONSISTENT_PARAMS:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_INCONSISTENT_PARAMS";
		break;
	case INM_WIFI_REASON_MESH_INVALID_SECURITY_CAP:
		pszDisconnectReason = "INM_WIFI_REASON_MESH_INVALID_SECURITY_CAP";
		break;
	case 0:
		pszDisconnectReason = "INM_WIFI_NOT_DISCONNECTED";
		break;
	default:
		pszDisconnectReason = NULL;
		break;
	}
	return pszDisconnectReason;
}

int InmGetAnyProfile(inm_connection_h *profile)
{
	int  nRet = inm_get_current_connection(g_hInm, profile);
	PRINT_RESULT_NORETURN(nRet, INM_ERROR_NONE, "inm_get_current_connection", InmGetError(nRet));

	return 0;
}

bool InmForeachFoundApCallback(inm_connection_h ap, void *user_data)
{
	PRINT_RETURN("inm_foreach_found_ap_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
	return false;
}

void InmWifiStateChangedCallback(inm_wifi_state_e result, void* user_data)
{
	PRINT_RETURN("inm_wifi_state_changed_callback", result);
	g_nCallbackRet = true;
}

void InmWifiScanStateChangedCallback(inm_wifi_scan_state_e state, void* user_data)
{
	PRINT_RETURN("inm_wifi_scan_state_changed_callback", state);
	g_nCallbackRet = true;
}

bool 	InmConnectionStateChangedCallback(inm_connection_state_e state, void* user_data)
{
	char *pszProfileName = NULL;
	inm_connection_h profile = user_data;

	if (profile == NULL)
		return false;

	int nRet = inm_connection_get_name(profile, NULL);
	PRINT_RETURN("inm_connection_get_name", nRet);
	if (nRet != INM_ERROR_NONE) {
		FREE_MEMORY_TC(pszProfileName);
		return false;
	}
	g_nCallbackRet = true;
	FREE_MEMORY_TC(pszProfileName);
	return true;
}

bool InmWifiApForeachVsieCallback(unsigned char *vsie_bytes, int vsie_len, void *user_data)
{
	PRINT_RETURN("inm_wifi_ap_foreach_vsie_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
	return false;
}

void InmSetEthernetCableStateChangedCallback(inm_ethernet_cable_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_ethernet_cable_state_changed_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetIpConflictCallback(char *if_name, char *ip, inm_ip_conflict_state_e state, void *user_data)
{
	PRINT_RETURN("inm_set_ip_conflict_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetCongestionLevelCallback(inm_congestion_level_e result, void* user_data)
{
	PRINT_RETURN("inm_set_congestion_level_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetRetryTxRateCallback(int rate, void* user_data)
{
	PRINT_RETURN("inm_set_retry_tx_rate_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetChannelInterferenceCallback(int freq, double channel_intf, void* user_data)
{
	PRINT_RETURN("inm_set_channel_interference_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetCellularStateChangedCallback(inm_cellular_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetWifiStateChangedCallback(inm_wifi_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

void InmSetEthernetStateChangedCallback(inm_ethernet_state_e result, void* user_data)
{
	PRINT_RETURN("inm_set_cellular_state_changed_callback", INM_ERROR_NONE);
	g_nCallbackRet = true;
}

int InmGetCurrentLink(inm_link_h *hRefLinkHandle)
{
	inm_connection_h hProfileHandle = NULL;
	inm_connection_type_e eConnType = -1;

	int nRet = inm_get_current_connection(g_hInmHandle, &hProfileHandle);
	if (nRet != INM_ERROR_NONE) 
	{
		FPRINTF("[Line : %d][%s] inm_get_current_connection failed.\\n", __LINE__, API_NAMESPACE);
		return nRet;
	}
	if(hProfileHandle == NULL)
	{
		FPRINTF("[Line : %d][%s] inm_get_current_connection failed. hProfileHandle is NULL\\n", __LINE__, API_NAMESPACE);
		return INM_ERROR_INVALID_PARAMETER;
	}

	nRet = inm_connection_get_type(hProfileHandle, &eConnType);
	if (nRet != INM_ERROR_NONE) 
	{
		FPRINTF("[Line : %d][%s] inm_connection_get_type failed.\\n", __LINE__, API_NAMESPACE);
		inm_connection_destroy(&hProfileHandle);
		return nRet;
	}
	if (eConnType != INM_CONNECTION_TYPE_WIFI && eConnType != INM_CONNECTION_TYPE_ETHERNET)
	{
		FPRINTF("[Line : %d][%s] inm_connection_get_type failed. eConnType is an invalid value\\n", __LINE__, API_NAMESPACE);
		inm_connection_destroy(&hProfileHandle);
		return INM_ERROR_INVALID_PARAMETER;
	}

	nRet = inm_connection_get_link(hProfileHandle, hRefLinkHandle);
	if (nRet != INM_ERROR_NONE) 
	{
		FPRINTF("[Line : %d][%s] inm_connection_get_link failed.\\n", __LINE__, API_NAMESPACE);
		inm_connection_destroy(&hProfileHandle);
		return nRet;
	}

	nRet = inm_connection_destroy(&hProfileHandle);
	if (nRet != INM_ERROR_NONE) 
	{
		FPRINTF("[Line : %d][%s] inm_connection_destroy failed.\\n", __LINE__, API_NAMESPACE);
		return nRet;
	}

	return 0;
}

/**
* @function         CapiNetworkInmTimeout
* @description      Called if some callback is not invoked for a particular timeout
* @parameter        gpointer data
* @return           gboolean
*/

gboolean CapiNetworkInmTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		dlog_print(DLOG_INFO, "NativeTCT", "[%d:%s] Quit mainloop(timeout)[%p]", __LINE__, __FUNCTION__, pMainLoop);
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[%d:%s] Callback Timeout\\n", __LINE__, __FUNCTION__);
	return false;
}

/** @} */
