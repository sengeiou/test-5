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
#include "ITs-context-common.h"

/** @addtogroup itc-context
* @ingroup		itc
* @{
*/

//Add helper function definitions here

/**
* @function 		ContextHistoryGetHistoryData
* @description	 	Maps context history data enums to string values
* @parameter		eDataVal : context history data returned
* @return 			context history data string
*/
char* ContextHistoryGetHistoryData(context_history_data_e eDataVal)
{
	char *pszDataVal = NULL;
	switch ( eDataVal )
	{
		case CONTEXT_HISTORY_RECENTLY_USED_APP:
			pszDataVal = "CONTEXT_HISTORY_RECENTLY_USED_APP";
			break;
		case CONTEXT_HISTORY_FREQUENTLY_USED_APP:
			pszDataVal = "CONTEXT_HISTORY_FREQUENTLY_USED_APP";
			break;
		case CONTEXT_HISTORY_BATTERY_USAGE:
			pszDataVal = "CONTEXT_HISTORY_BATTERY_USAGE";
			break;
		case CONTEXT_HISTORY_RECENT_BATTERY_USAGE:
			pszDataVal = "CONTEXT_HISTORY_RECENT_BATTERY_USAGE";
			break;
		default:
			pszDataVal = "Unknown Value";
			break;
	}

	return pszDataVal;
}

/**
* @function 		ContextHistoryGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ContextHistoryGetError(int nRet)
{
	char *pszErrorVal = NULL;
	switch ( nRet )
	{
		case CONTEXT_HISTORY_ERROR_NONE:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NONE";
			break;
		case CONTEXT_HISTORY_ERROR_INVALID_PARAMETER:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_INVALID_PARAMETER";
			break;
		case CONTEXT_HISTORY_ERROR_PERMISSION_DENIED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_PERMISSION_DENIED";
			break;
		case CONTEXT_HISTORY_ERROR_NOT_SUPPORTED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NOT_SUPPORTED";
			break;
		case CONTEXT_HISTORY_ERROR_OUT_OF_MEMORY:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OUT_OF_MEMORY";
			break;
		case CONTEXT_HISTORY_ERROR_NO_DATA:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_NO_DATA";
			break;
		case CONTEXT_HISTORY_ERROR_OUT_OF_RANGE:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OUT_OF_RANGE";
			break;
		case CONTEXT_HISTORY_ERROR_OPERATION_FAILED:
			pszErrorVal = "CONTEXT_HISTORY_ERROR_OPERATION_FAILED";
			break;
		default:
			pszErrorVal = "Unknown Error";
			break;
	}

	return pszErrorVal;
}

#if defined  (MOBILE ) || defined  (TIZENIOT)
/**
* @function 		ContextTriggerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* ContextTriggerGetError(int nRet)
{
	char *pszErrorVal = NULL;
	switch ( nRet )
	{
		case CONTEXT_TRIGGER_ERROR_NONE:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_NONE";
			break;
		case CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_INVALID_PARAMETER";
			break;
		case CONTEXT_TRIGGER_ERROR_OUT_OF_MEMORY:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_OUT_OF_MEMORY";
			break;
		case CONTEXT_TRIGGER_ERROR_PERMISSION_DENIED:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_PERMISSION_DENIED";
			break;
		case CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED";
			break;
		case CONTEXT_TRIGGER_ERROR_NO_DATA:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_NO_DATA";
			break;
		case CONTEXT_TRIGGER_ERROR_OPERATION_FAILED:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_OPERATION_FAILED";
			break;
		case CONTEXT_TRIGGER_ERROR_RULE_ENABLED:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_RULE_ENABLED";
			break;
		case CONTEXT_TRIGGER_ERROR_RULE_NOT_ENABLED:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_RULE_NOT_ENABLED";
			break;
		case CONTEXT_TRIGGER_ERROR_INVALID_RULE:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_INVALID_RULE";
			break;
		case CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_RULE_NOT_EXIST";
			break;
		case CONTEXT_TRIGGER_ERROR_DATA_EXIST:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_DATA_EXIST";
			break;
		case CONTEXT_TRIGGER_ERROR_INVALID_DATA:
			pszErrorVal = "CONTEXT_TRIGGER_ERROR_INVALID_DATA";
			break;
		default:
			pszErrorVal = "Unknown Error";
			break;
	}

	return pszErrorVal;
}

/**
* @function 		ContextTriggerEvent
* @description	 	Maps trigger event enums to string values
* @parameter		nRet : trigger event enums
* @return 			event string
*/
char* ContextTriggerEvent(context_trigger_event_e eTriggerEvent)
{
	char *pszTriggerEvent = NULL;
	switch ( eTriggerEvent )
	{
		case CONTEXT_TRIGGER_EVENT_TIME:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_TIME";
			break;
		case CONTEXT_TRIGGER_EVENT_BATTERY:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_BATTERY";
			break;
		case CONTEXT_TRIGGER_EVENT_CHARGER:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_CHARGER";
			break;
		case CONTEXT_TRIGGER_EVENT_GPS:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_GPS";
			break;
		case CONTEXT_TRIGGER_EVENT_HEADPHONE:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_HEADPHONE";
			break;
		case CONTEXT_TRIGGER_EVENT_USB:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_USB";
			break;
		case CONTEXT_TRIGGER_EVENT_WIFI:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_WIFI";
			break;
		case CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE";
			break;
		case CONTEXT_TRIGGER_EVENT_CALL:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_CALL";
			break;
		case CONTEXT_TRIGGER_EVENT_EMAIL:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_EMAIL";
			break;
		case CONTEXT_TRIGGER_EVENT_MESSAGE:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_MESSAGE";
			break;
		case CONTEXT_TRIGGER_EVENT_CONTACTS:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_CONTACTS";
			break;
		case CONTEXT_TRIGGER_EVENT_PLACE:
			pszTriggerEvent = "CONTEXT_TRIGGER_EVENT_PLACE";
			break;
		default:
			pszTriggerEvent = "Unknown Event";
			break;
	}

	return pszTriggerEvent;
}
#endif	//MOBILE OR TIZENIOT

/** @} */ //end of itc-context
