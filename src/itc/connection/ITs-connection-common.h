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
#ifndef _ITS_CONNECTION_COMMON_H_
#define _ITS_CONNECTION_COMMON_H_

/************************** Headers **********************************************/

#include "tct_common.h"

#include <net_connection.h>

#include <glib-2.0/glib.h>
#include <tone_player.h>

/************************************************************************/


/** @addtogroup itc-connection
*  @ingroup itc
*  @{
*/

bool g_bFeatureSupported;
bool g_bFeatureMismatch;
bool g_bFeatureNotSupported;

#define MICROSECONDS_PER_SECOND		1000000
#define WIFI_FEATURE				"http://tizen.org/feature/network.wifi"

#define TETHERING_BLUETOOTH_FEATURE		"http://tizen.org/feature/network.tethering.bluetooth"


#define TELEPHONY_FEATURE			"http://tizen.org/feature/network.telephony"
#define ETHERNET_FEATURE			"http://tizen.org/feature/network.ethernet"
#define API_NAMESPACE				"CONNECTION_ITC"

//helper function declarations here

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bFeatureMismatch )\
{\
	return 1;\
}\
	if ( g_bFeatureNotSupported )\
{\
	return 0;\
}\
}


char* ConnectionGetError(connection_error_e nRet);
char* ConnectionGetCellularStateType(connection_cellular_state_e nState);
char* ConnectionGetType(connection_type_e nType);
char* ConnectionGetAddressFamily(connection_address_family_e nFamily);
char* ConnectionGetCellularServiceType(connection_cellular_service_type_e nRet);
char* ConnectionGetCellularAuthType(connection_cellular_auth_type_e nRet);
char* ConnectionGetIpConfigType(connection_ip_config_type_e nRet);
char* ConnectionGetProxyType(connection_proxy_type_e nType);
char* ConnectionGetIteratorType(connection_iterator_type_e nType);
char* ConnectionGetStatisticTypeData(connection_statistics_type_e nType);
int ConnectionManager_get_MMS_type(connection_h connection,connection_profile_h *profile);
int ConnectionManager_get_celluar_profile(connection_h connection,connection_profile_h *profile);
int ConnectionManager_get_wifi_profile(connection_h connection,connection_profile_h *profile);
int ConnectionManager_get_celluar_profile_by_name(connection_h connection, char* profileName, connection_profile_h *profile);
#if (defined(MOBILE) || defined(WEARABLE)  || defined(TIZENIOT)) || defined(TV) //Starts MOBILE or WEARABLE or TIZENIOT
char* ConnectionGetCellularPdnType(connection_cellular_pdn_type_e nRet);
#endif  // End MOBILE or WEARABLE or TIZENIOT
/** @} */ 

#endif  //_ITS_CONNECTION_COMMON_H_
