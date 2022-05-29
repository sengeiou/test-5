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
#ifndef _ITS_BLUETOOTH_COMMON_H_
#define _ITS_BLUETOOTH_COMMON_H_

#include "tct_common.h"
#include "bluetooth.h"
#include <storage.h>
#include <app.h>
#include <glib-2.0/glib.h>
#include <math.h>

/** @addtogroup itc-bluetooth
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE					"BLUETOOTH_ITC"
#define CONFIG_LINE_LEN_MAX				2048	//maximum key-value line length
#define CONFIG_VALUE_LEN_MAX			1024	//maximum length of value 
#define EXECUTE_MANUAL					0
#define ADAPTER_NAME					"BT_TEST"
#define ADAPTER_NAME_LENGTH				15
#define BLUETOOTH_UUID_LENGTH			50
#define SHORT_DELAY						2000
#define LONG_DELAY						5000
#define CALLBACK_DELAY					40000
#define PATH_LEN						1024
#define OPP_FILE_NAME					"TestFile.vcf"
#define BLUETOOTH_SERVICE_UUID			"00001105-0000-1000-8000-00805f9b34fb"	
#define SLEEP_TIME						5
#define BLUETOOTH_FEATURE				"http://tizen.org/feature/network.bluetooth"
#define BLUETOOTH_OPP_FEATURE			"http://tizen.org/feature/network.bluetooth.opp"
#define BLUETOOTH_AUDIOMEDIA_FEATURE	"http://tizen.org/feature/network.bluetooth.audio.media"
#define BLUETOOTH_AUDIOCALL_FEATURE		"http://tizen.org/feature/network.bluetooth.audio.call"
#define BLUETOOTH_LE_FEATURE			"http://tizen.org/feature/network.bluetooth.le"
#define BLUETOOTH_OOB_FEATURE			"http://tizen.org/feature/network.bluetooth.oob"
#define BLUETOOTH_LE5_FEATURE			"http://tizen.org/feature/network.bluetooth.le.5_0"


bool g_bBluetoothInit;
bool g_bBluetoothMismatch;
bool g_bBluetoothNotSupported;
bool g_bBluetoothIsSupported;
bool g_bBluetoothIsOPPSupported;
bool g_bBluetoothIsAudioSupported;
bool g_bBluetoothIsLESupported;
bool g_bBluetoothIsOOBSupported;


bool g_bCallbackResult;

GMainLoop *g_pMainLoop;

gboolean TimeoutFunction(gpointer data);

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( g_bBluetoothMismatch )\
	{\
	FPRINTF("[Line : %d][%s] Feature support as returned by BluetoothCheckSystemInfoFeatureSupported() and error code as returned by bt_initialize() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
	else if ( g_bBluetoothNotSupported )\
	{\
	FPRINTF("[Line : %d][%s] Bluetooth feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 0;\
	}\
	if ( !g_bBluetoothInit )\
	{\
	FPRINTF("[Line : %d][%s] Precondition of bluetooth initialaztion failed, Leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
	}\
}

#define CHECK_CALLBACK_STATUS(szApiName) {\
	nTimeoutId = g_timeout_add(CALLBACK_DELAY, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	if ( g_bCallbackResult == false )\
	{\
	FPRINTF("[Line : %d][%s] After %s, callback has not been invoked\\n", __LINE__, API_NAMESPACE, szApiName);\
	return 1;\
	}\
	else\
	{\
	g_bCallbackResult = false;\
	}\
}

#define CHECK_UNSET_CALLBACK_STATUS(nTime, szApiName)\
	nTimeoutId = g_timeout_add(nTime, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\
	if ( g_bCallbackResult == true )\
	{\
	FPRINTF("[Line : %d][%s] After %s, callback is invoked\\n", __LINE__, API_NAMESPACE, szApiName);\
	return 1;\
	}\

#define WAIT(nTime)\
	g_pMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(nTime, TimeoutFunction, g_pMainLoop);\
	g_main_loop_run(g_pMainLoop);\
	g_source_remove(nTimeoutId);\


char* BluetoothGetError(int nRet);
char* BluetoothGetEnumString(bt_adapter_visibility_mode_e enum_discoverable_mode);
char* BluetoothGetPacketTypeEnumString(int nRet);
bool BluetoothInitAudio(char *pszRemoteDeviceAddress);
void BluetoothDeinitAudio(char *pszRemoteDeviceAddress);
bool BluetoothGetStorageDownloadsPath(char *pszPath);
bool BluetoothGetDataPath(char* pPath);
char* StorageGetError(storage_error_e nRet);
/** @} */
#endif  //_ITS_BLUETOOTH_COMMON_H_
