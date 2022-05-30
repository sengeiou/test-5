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
#ifndef _ITS_TELEPHONY_COMMON_H_
#define _ITS_TELEPHONY_COMMON_H_

#include "tct_common.h"
#include <telephony.h>
#include <net_connection.h>

/** @addtogroup itc-telephony
*  @ingroup itc
*  @{
*/

#define LOG							100
#define TIME_DELAY					20
#define USLEEPDELAY					500000
#define GMAINTIMEOUT				2000
#define API_NAMESPACE				"TELEPHONY_ITC"
#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define WIFI_FEATURE				"http://tizen.org/feature/network.wifi"
#define TETHERING_BLUETOOTH_FEATURE	"http://tizen.org/feature/network.tethering.bluetooth"
#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define ETHERNET_FEATURE			"http://tizen.org/feature/network.ethernet"

//Add helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bTelephonySkipExecutionWithPass == true )\
	{\
	FPRINTF("[Line : %d][%s] telephony is not supported on the device, telephony_init returned TIZEN_ERROR_NOT_SUPPORTED, also feature http://tizen.org/feature/network.telephony value returned from model-config.xml is false\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	else if ( g_bTelephonySkipExecutionWithFail == true )\
	{\
	FPRINTF("[Line : %d][%s] telephony_init did not return TIZEN_ERROR_NOT_SUPPORTED, while feature %s value returned from model-config.xml is false \\n", __LINE__, API_NAMESPACE, TELEPHONY_FEATURE);\
	return 1;\
	}\
	if ( !g_bTelephonyInit )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of telephony failed\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
	if ( g_stTelephonyHandleList.handle[0] == NULL )\
	{\
	FPRINTF("[Line : %d][%s] telephony handle list is empty \\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define CHECK_SIM_STATE {\
	telephony_sim_state_e eSimState;\
	nRet = telephony_sim_get_state(g_pstTelephonySIMHandle, &eSimState);\
	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_sim_get_state", TelephonyGetError(nRet));\
	if ( eSimState != TELEPHONY_SIM_STATE_AVAILABLE )\
	{\
	FPRINTF("[Line : %d][%s] telephony_sim_get_state returned state = %s \\n", __LINE__, API_NAMESPACE, TelephonyGetSimState(eSimState));\
	return 1;\
	}\
}

char *TelephonyGetError(int nRet);
char *TelephonyGetServiceState(telephony_network_service_state_e eRet);
char *TelephonyGetSimState(telephony_sim_state_e eRet);
char *TelephonyGetSimLockState(telephony_sim_lock_state_e eRet);
char *TelephonyGetRSSIValue(telephony_network_rssi_e eRet);
char *TelephonyGetNetworkType(telephony_network_type_e eRet);
char *TelephonyGetState(telephony_state_e eRet);
bool TelephonyGetSimHandle(int nSlotCount);
char *TelephonyGetNetworkSelMode(telephony_network_selection_mode_e eRet);
char* ConnectionGetError(connection_error_e nRet);
/** @} */
#endif  //_ITS_TELEPHONY_COMMON_H_
