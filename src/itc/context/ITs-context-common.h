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
#ifndef _ITS_CONTEXT_COMMON_H_
#define _ITS_CONTEXT_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"
#include <context_history.h>
#if defined  (MOBILE ) || defined  (TIZENIOT)
#include <context_trigger.h>
#endif	//MOBILE OR TIZENIOT

/** @addtogroup itc-context
* @ingroup		itc
* @{
*/

bool g_bHistoryMismatch;
bool g_bHistoryNotSupported;
bool g_bIsHistoryFeatureSupported;
#if defined  (MOBILE ) || defined  (TIZENIOT)
bool g_bTriggerMismatch;
bool g_bTriggerNotSupported;
bool g_bIsTriggerFeatureSupported;
#endif	//MOBILE OR TIZENIOT

//Add test package related includes here
#define HISTORY_FEATURE				"http://tizen.org/feature/app_history"
#define BATTERY_FEATURE				"http://tizen.org/feature/battery"
#if defined  (MOBILE ) || defined  (TIZENIOT)
#define TRIGGER_FEATURE				"http://tizen.org/feature/contextual_trigger"
#endif	//MOBILE OR TIZENIOT

#define API_NAMESPACE				"Context_ITC"
#define RECORD_INT_KEY				CONTEXT_HISTORY_TOTAL_COUNT
#define RECORD_STRING_KEY			CONTEXT_HISTORY_APP_ID
#define TEST_TESTAPPLICATION_APPID	"org.tizen.testapplication"
#define TEST_HELLOWORLD_APPID		"org.tizen.helloworld"
#define SET_INT_VAL					200
#define INT_VAL1					30
#define INT_VAL2					10
#define ADD_COMP_INT_VAL			960
#define ADD_OPTION_INT_VAL			1

#if defined  (MOBILE ) || defined  (TIZENIOT)
#define CONTEXT_TEST_PACKAGE_ID "native-context-itc"
#define CUSTOM_ITEM_WEATHER "weather"
#define CUSTOM_WEATHER_TEMPLATE "{ \"temperature\": { \"type\": \"integer\", \"minimum\": -50, \"maximum\": 50}, \"status\": { \"enum\": [ \"sunny\", \"snowy\", \"cloudy\", \"rainy\"]} }"
#define CUSTOM_WEATHER_DATA1 "{\"temperature\": 30, \"status\":\"sunny\"}"
#endif	//MOBILE OR TIZENIOT

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
}

#define START_TEST_HISTORY {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bHistoryMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by context_history_is_supported() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bHistoryNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}

#if defined  (MOBILE ) || defined  (TIZENIOT)
#define START_TEST_TRIGGER {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE,__FUNCTION__);\
	if ( g_bTriggerMismatch )\
	{\
		FPRINTF("[Line : %d][%s] Feature support as returned by TCTCheckSystemInfoFeatureSupported() and error code as returned by context_trigger_rule_event_is_supported() mismatched, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 1;\
	}\
	else if ( g_bTriggerNotSupported )\
	{\
		FPRINTF("[Line : %d][%s] feature not supported, Leaving test\\n", __LINE__, API_NAMESPACE);\
		return 0;\
	}\
}
#endif	//MOBILE OR TIZENIOT

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
    if ( Handle == NULL )\
    {\
        FPRINTF("[Line: %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
        FreeResource;\
        return 1;\
    }\
}

//Add helper function declarations here
char* ContextHistoryGetError(int nRet);
char* ContextHistoryGetHistoryData(context_history_data_e eDataVal);

#if defined  (MOBILE ) || defined  (TIZENIOT)
char* ContextTriggerGetError(int nRet);
char* ContextTriggerEvent(context_trigger_event_e eTriggerEvent);
#endif	//MOBILE OR TIZENIOT

/** @} */ //end of itc-context

#endif  //_ITS_CONTEXT_COMMON_H_
