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
#ifndef _CTS_PLATFORM_PERMISSION_COMMON_H_
#define _CTS_PLATFORM_PERMISSION_COMMON_H_

//Add test package related includes here

#include "tct_common.h"
#include "tct_app_common.h"

#include <runtime_info.h>
#include <locations.h>
#include <bluetooth.h>
#include <net_connection.h>
#include <device/power.h>
#include <device/haptic.h>
#include <device/display.h>
#include <device/callback.h> 
#include <recorder.h>
#include <camera.h>
#include <package_manager.h>
#include <messages.h>
//#include <msg.h>
#include <push-service.h>
#include <device/ir.h>

#ifdef MOBILE		//Starts MOBILE
#include <contacts.h>
#include <calendar.h>
#include <email.h>
#include <download.h>
#endif  //MOBILE	//End MOBILE

#include <sound_manager.h>
#include <system_settings.h>
#include <notification.h>
#include <app_manager.h>
#include <media_content.h>
#include <telephony.h>
#include <app.h>
#include <player.h>
#include <sensor.h>
#include <device/led.h> 
#include <data_control.h>
#include <message_port.h>
#include <audio_io.h>
#include <wav_player.h>
#include <account.h>
#include <badge.h>
#include <wifi-manager.h>

#ifdef MOBILE
#include <shortcut_manager.h>
#include <ckmc/ckmc-manager.h>
#include <oauth2.h>
#endif
#include <app_alarm.h>
#include "app.h"
#include <storage.h>
#include <nfc.h>
#include <glib.h>
#ifdef MOBILE
#include "context_history.h"
#include <wifi-direct.h>
#endif
#include <smartcard.h>
#include "maps_service.h"
#include "maps_error.h"
#include <media_controller_client.h>
#include <media_controller_server.h>
#include <media_controller_type.h>
#include <widget_service.h>
#include <widget_errno.h>
//#include <widget_service_internal.h>
#ifdef MOBILE
#include <minicontrol-viewer.h>
#include <minicontrol-provider.h>
//#include <minicontrol-monitor.h>
#endif
#include <efl_util.h>
#include <Elementary.h>
#include "runtime_info.h"
#include "inputmethod_manager.h"
#include <inputmethod.h>
/** @addtogroup ctc-platform-permission
* @ingroup		ctc
* @{
*/

#define API_NAMESPACE					"PLATFORM_PERMISSION_CTC"
#define PACKAGE_NAME					"org.tizen.testapplication"
#define NAME_CER						"PASSWORD"
#define PASSWORD_CER					"12345"
#define TESTSTRING						"Test"
#define TESTPACKAGE						"org.tizen.testwidget-1.0.0"
#define MAX_BLOCK_SIZE 					25
#define SECONDARYAPPID					"org.tizen.appmanagertestfile"
#define MINICONTROL_NAME 				"minicontrol-itc"
#define CONF_FIELD_LENGTH				200
#define SOUND_MANAGER_VOLUME_LEVEL		8
#define INTERNAL_STORAGE				1
#define EXTERNAL_STORAGE				0
#define MEDIA_IMAGE_PATH				1
#define FILE_NAME						"/PlatformPermission_test.jpg"
#define BADGE_PACKAGE					"native-platform-permission-ctc-0.1-0."
#define APPID							"7c58a4ac98388bba"
#define CAMERA_WAIT_TIME				5
#define CAMERA_WAIT_GLOOP				3
#define INT_VAL1						30
#define BUFFER							50
#define PATH_LEN						1024
#define INT_VAL2						10
#define PUSH_TEST_APP_ID 				"TEST_APP_ID"
#define PUSH_TEST_CONTENT_TYPE 			"text/vnd.wap.connectivity-xml"
#define PROVIDERID						"http://tizen.org/datacontrol/provider/datacontrolprovider"
#define FEATURE_AUDIO_MICROPHONE		"http://tizen.org/feature/microphone"
#define FEATURE_AUDIO_CAMERA			"http://tizen.org/feature/camera"	
#define FEATURE_CAMERA_BACK 			"http://tizen.org/feature/camera.back"
#define FEATURE_CAMERA_FRONT			"http://tizen.org/feature/camera.front"
#define FEATURE_NETWORK_TELEPHONY		"http://tizen.org/feature/network.telephony"
#define FEATURE_BLUETOOTH				"http://tizen.org/feature/network.bluetooth"
#define FEATURE_WIFIDIRECT				"http://tizen.org/feature/network.wifi.direct"
#define FEATURE_NFC						"http://tizen.org/feature/network.nfc"
#define FEATURE_LOCATION				"http://tizen.org/feature/location"
#define FEATURE_DISPLAY					"http://tizen.org/feature/camera.back.flash"
#define WIFI_FEATURE					"http://tizen.org/feature/network.wifi"
#define TELEPHONY_FEATURE				"http://tizen.org/feature/network.telephony"
#define SE_UICC_FEATURE					"http://tizen.org/feature/network.secure_element.uicc"
#define SE_ESE_FEATURE					"http://tizen.org/feature/network.secure_element.ese"
#define FEATURE_MSGWRITE				"http://tizen.org/feature/network.telephony.sms"
#define SM_WIFI_DIRECT_FEATURE 			"http://tizen.org/feature/network.wifi.direct.display"
#define FEATURE_WIDGET					"http://tizen.org/feature/shell.appwidget"
#define FEATURE_CARDEMULATION			"http://tizen.org/feature/network.nfc.card_emulation"
#define FEATURE_HRM_SENSOR 				"http://tizen.org/feature/sensor.heart_rate_monitor"
#define FEATURE_BLUETOOTH_LE			"http://tizen.org/feature/network.bluetooth.le"
#define FEATURE_BLUETOOTH_HDP			"http://tizen.org/feature/network.bluetooth.health"
#define FEATURE_BLUETOOTH_AUDIO_MEDIA		"http://tizen.org/feature/network.bluetooth.audio.media"
#define FEATURE_BLUETOOTH_TETHERING     	"http://tizen.org/feature/network.tethering.bluetooth"
#define FEATURE_BLUETOOTH_OPP    		"http://tizen.org/feature/network.bluetooth.opp"
#define FEATURE_BLUETOOTH_CALL			"http://tizen.org/feature/network.bluetooth.audio.call"
#define FEATURE_BLUETOOTH_GATT_CLIENT	"http://tizen.org/feature/network.bluetooth.le.gatt.client"
#define FEATURE_CAMERA_BACK_FLASH		"http://tizen.org/feature/camera.back.flash"
#define FEATURE_CAMERA_FRONT_FLASH		"http://tizen.org/feature/camera.front.flash"
#define FEATURE_GPS						"http://tizen.org/feature/location.gps"
#define FEATURE_WIFIDIRECT_DISPLAY		"http://tizen.org/feature/network.wifi.direct.display"
#define FEATURE_WIFIDIRECT_DISCOVERY		"http://tizen.org/feature/network.wifi.direct.service_discovery"
#define FEATURE_NETWORK_WIFI			"http://tizen.org/feature/network.wifi"
#define FEATURE_NETWORK_WIFI_TDLS		"http://tizen.org/feature/network.wifi.tdls"
#define FEATURE_SHORTCUT			"http://tizen.org/feature/shortcut"
#define	TPK1					"native-testapp-itc"
#define	TPK2					"org.tizen.appmanagertestfile"
#define	TPK3					"org.tizen.datacontrolprovider"
#define	TPK4					"org.tizen.helloworld"
#define	TPK5					"org.tizen.testapplication"
#define FEATURE_TELEPHONY               "http://tizen.org/feature/network.telephony"
#define FEATURE_CONTACT                 "http://tizen.org/feature/contact"
#define FEATURE_EMAIL               "http://tizen.org/feature/email"
#define FEATURE_CALENDAR		"http://tizen.org/feature/calendar"
#define FEATURE_CAPI_MAPS		"http://tizen.org/feature/maps"
#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define PRINT_RESULT_ERROR_NONE(eCompare, eRetVal, API, Error, FreeResource, ERROR_NONE) {\
	if ( eRetVal == eCompare )\
{\
	if ( DEBUG )\
	{\
		FPRINTF("[Line : %d][%s] %s passed\\n", __LINE__, API_NAMESPACE, API);\
	}\
}\
else \
{\
	FPRINTF("[Line : %d][%s] %s failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, API, Error, eRetVal);\
	FreeResource;\
	return 1;\
}\
}

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
    if ( Handle == NULL )\
    {\
        FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
    }\
}

enum async_state
{
	CAMERA_ASYNC_READY,
	CAMERA_ASYNC_DONE
};
int g_nDownloadId;
bool g_bIsSupported;

messages_service_h g_hMessagesService;

#ifdef MOBILE	//Starts MOBILE
contacts_record_h g_hContactRecord;
#endif  //MOBILE	//End MOBILE

messages_message_h g_hMessage;
telephony_h g_hTelephony;
telephony_handle_list_s g_hTelephonyList;
camera_h 	g_hCamera;
connection_h g_hConnection;
package_manager_h g_hPackageManager;
package_info_h g_hPackageInfo;
app_control_h g_hAppControl;
#ifdef MOBILE	//Starts MOBILE
context_history_h g_hContxtHist;
context_history_filter_h g_hContxtHistFilter;
#endif  //MOBILE	//End MOBILE

bool g_bIsSetAFModePassed;
recorder_h g_hRecorder;
char g_szWidgetid[PATH_LEN];
char g_szPkgid[PATH_LEN];
char g_szMapsProvider[BUFFER];

GMainLoop *g_pMainLoop;
bool g_bLibStorageCallbackHit;
bool g_bLibStorageCallbackResultValid;
gboolean TimeoutFunction(gpointer data);
int g_nLibInternalStorageId;
int g_nLibExternalStorageId;
bool g_bLibStorageIsInternal;
bool g_bLibStorageIsExternal;

char* BadgePrintErrorCode(int nResult);
#ifdef MOBILE
char* ShortcutPrintErrorCode(int nResult);
#endif
char* RecorderPrintErrorMsg(int nRet);
char* SoundManagerPrintErrorInfo(int nResult);
char* LocationsPrintErrorInfo(int nResult);
char* BluetoothPrintErrorInfo(int nResult);
char* TelServicePrintAPIErrorMSG(int nError);
char* AppControlPrintErrorInfo(int nResult);
char* DevicePrintErrorInfo(int nResult);
char* EmailPrintErrorInfo (int nResult);
char* PushServicePrintErrorInfo(int nRet);
char* MessagesPrintErrorInfo(int nResult);
char* NotificationPrintAPIErrorMSG(int nRet);
char* PackageManagerPrintErrorInfo(int nResult);
char* AlarmPrintErrorInfo(int nResult);
char* DownloadPrintErrorInfo(int nResult);
char* CameraPrintErrorMsg(int nRet);
char* NetworkConnectionPrintErrorMsg(int nRet);

#ifdef MOBILE	//Starts MOBILE
char* ContactsPrintErrorCode(int nResult);
char* CalendarPrintErrorInfo(int nResult);
#endif  //MOBILE	//End MOBILE

char* SystemSettingsPrintErrorInfo(int nResult);
char* AccountManagerPrintErrorCode(int nResult);
char* MediaContentPrintErrorInfo(int nResult);
char* DataControlPrintErrorInfo(int nResult);
char* WifiDirectPrintErrorInfo(int nResult);
char* NfcPrintErrorInfo(int nResult);
char* StoragePrintErrorInfo(int nResult);
bool get_storage_id_callback();
char* MediaControllerGetError(int nRet);
char* MapServiceGetError(int nRet);
char* AppManagerGetError(int nRet);
char* SmartcardGetErrorCode(int nRet);
char* SmartcardGetError(int nRet);
char* WidgetServiceGetError(int nRet);
#ifdef MOBILE
char* MinicontrolGetError(minicontrol_error_e nRet);
#endif
char* EflUtilGetError(int nRet);
char* MessagesGetError(int nRet);
char* Oauth2InfoGetError(int nRet);
char* PackageManagerGetError(int nRet);
char* RuntimeInfoGetError(int nRet);
char* NFCGetError(int nRet);
char* SensorsGetError(int nRet);
char* InputmethodManagerGetError(int nRet);
char* InputmethodGetError(int nRet);
void EflUtilDeleteWindow(void *pData, Evas_Object *pstWindow, void *pEvent);
bool EflUtilCreateNotificationWindow(Evas_Object **pstWindow);
int IotconGetSvrDBPath(char **path);
#ifdef MOBILE	//Starts MOBILE
char* ContextHistoryGetError(int nRet);
#endif  //MOBILE	//End MOBILE

//////////////////////////////////////////

bool BluetoothStateIsEqual(bt_adapter_state_e eAdapterState);
bool TelServiceInitializeHandler();
bool TelServiceDeInitializeHandler();

#ifdef MOBILE	//Starts MOBILE
bool ContactRecordDestroy();
bool ContactDisconnect();
bool ContactRecordCreate();
bool ContactConnect();
#endif  //MOBILE	//End MOBILE

bool AppControlCreate();
bool AppControlDestroy();
bool MediaContentConnect();
bool MediaContentDisconnect();
bool CreateMessage(messages_message_type_e eType);
bool DestroyMessage();
bool MessagesOpenService();
bool MessagesCloseService();
#ifdef MOBILE		//Starts MOBILE
bool EmailDestroyMessage(email_h hEmailHandle);
#endif  //MOBILE	//End MOBILE
bool PackageManagerDestroy();
bool GetArchType(char* pszArch);
#ifdef MOBILE		//Starts MOBILE
bool ContextHistCreate();
bool ContextHistDestroy();
#endif  //MOBILE	//End MOBILE

/** @} */ //end of ctc-platform-permission

#endif  //_PLATFORM_PERMISSION_COMMON_H_
