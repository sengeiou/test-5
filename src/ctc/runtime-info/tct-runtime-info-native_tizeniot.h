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
#ifndef __TCT_RUNTIME-INFO-NATIVE_H__
#define __TCT_RUNTIME-INFO-NATIVE_H__

#include "testcase.h"
#include "tct_common.h"

extern void CTs_runtime_info_startup(void);
extern void CTs_runtime_info_cleanup(void);

extern int CTc_RuntimeInfo_IsBluetoothEnabled_p(void);
extern int CTc_RuntimeInfo_IsWifiHotspotEnabled_p(void);
extern int CTc_RuntimeInfo_IsBluetoothTetheringEnabled_p(void);
extern int CTc_RuntimeInfo_IsUSBTetheringEnabled_p(void);
extern int CTc_RuntimeInfo_IsKeyPacketDataEnabled_p(void);
extern int CTc_RuntimeInfo_IsDataRoamingEnabled_p(void);
extern int CTc_RuntimeInfo_IsVibrationEnabled_p(void);
extern int CTc_RuntimeInfo_IsAudioJackConnectedEnabled_p(void);
extern int CTc_RuntimeInfo_IsBatteryCharging_p(void);
extern int CTc_RuntimeInfo_IsTVconnected_p(void);
extern int CTc_RuntimeInfo_IsUSBconnected_p(void);
extern int CTc_RuntimeInfo_IsChargerConnected_p(void);
extern int CTc_RuntimeInfo_IsAutoRotationEnabled_p(void);

testcase tc_array[] = {
	{"CTc_RuntimeInfo_IsBluetoothEnabled_p",CTc_RuntimeInfo_IsBluetoothEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsWifiHotspotEnabled_p",CTc_RuntimeInfo_IsWifiHotspotEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsBluetoothTetheringEnabled_p",CTc_RuntimeInfo_IsBluetoothTetheringEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsUSBTetheringEnabled_p",CTc_RuntimeInfo_IsUSBTetheringEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsKeyPacketDataEnabled_p",CTc_RuntimeInfo_IsKeyPacketDataEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsDataRoamingEnabled_p",CTc_RuntimeInfo_IsDataRoamingEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsVibrationEnabled_p",CTc_RuntimeInfo_IsVibrationEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsAudioJackConnectedEnabled_p",CTc_RuntimeInfo_IsAudioJackConnectedEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsBatteryCharging_p",CTc_RuntimeInfo_IsBatteryCharging_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsTVconnected_p",CTc_RuntimeInfo_IsTVconnected_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsUSBconnected_p",CTc_RuntimeInfo_IsUSBconnected_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsChargerConnected_p",CTc_RuntimeInfo_IsChargerConnected_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{"CTc_RuntimeInfo_IsAutoRotationEnabled_p",CTc_RuntimeInfo_IsAutoRotationEnabled_p,CTs_runtime_info_startup,CTs_runtime_info_cleanup},
	{NULL, NULL}
};

#endif // __TCT_RUNTIME-INFO-NATIVE_H__
