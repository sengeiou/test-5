//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#include "ITs-context-common.h"
#include <app.h>

/** @addtogroup itc-context
* @ingroup		itc
* @{
*/

//& set: Context
context_trigger_rule_h g_Handle;
context_trigger_rule_entry_h g_Event;
context_trigger_rule_entry_h g_Condition;
app_control_h g_AppHandle;

/**
* @function 		context_initialize_app_handle
* @description	 	Creates and initialize an app handle
* @parameter		NA
* @return 			bool, true or false
*/
bool context_initialize_app_handle(void)
{
	int nRet = app_control_create(&g_AppHandle);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_create failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet = app_control_set_operation(g_AppHandle, APP_CONTROL_OPERATION_DEFAULT);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_set_operation failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	nRet = app_control_set_app_id (g_AppHandle, TEST_TESTAPPLICATION_APPID);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_set_app_id failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	return true;
}

/**
* @function 		context_release_app_handle
* @description	 	Destroy an app handle
* @parameter		NA
* @return 			NA
*/
void context_release_app_handle(void)
{
	int nRet = app_control_destroy(g_AppHandle);
	if ( nRet != APP_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] app_control_destroy failed\\n", __LINE__, API_NAMESPACE);
	}
}

/**
* @function 		ITs_context_trigger_startup
* @description	 	Creates a context history handle
* @parameter		NA
* @return 			NA
*/
void ITs_context_trigger_startup(void)
{
	g_bTriggerMismatch = false;
	g_bTriggerNotSupported = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
	TCT_CheckInstalledApp(2, TEST_TESTAPPLICATION_APPID, TEST_HELLOWORLD_APPID);

	g_bIsTriggerFeatureSupported = TCTCheckSystemInfoFeatureSupported(TRIGGER_FEATURE, API_NAMESPACE);

	bool bSupported;
	int nRet = context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_BATTERY, &bSupported);
	if (!g_bIsTriggerFeatureSupported)
	{
		if (nRet == CONTEXT_TRIGGER_ERROR_NOT_SUPPORTED) {
			g_bTriggerNotSupported = true;
		} else {
			g_bTriggerMismatch = true;
		}
	}
}

/**
* @function 		ITs_context_trigger_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_context_trigger_cleanup(void)
{

	return;
}

/** @addtogroup	itc-context-testcases
* @brief 		Integration testcases for module context
* @ingroup		itc-context
* @{
*/

//& purpose: Creates an empty rule handle and releases the resources occupied by that rule handle
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_create_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an empty rule handle and releases the resources occupied by that rule handle
* @scenario				Create and destroy the rule handle
* @apicovered			context_trigger_rule_create, context_trigger_rule_destroy
* @passcase				When context_trigger_rule_create and context_trigger_rule_destroy are successful and return 0
* @failcase				If target API context_trigger_rule_create or context_trigger_rule_destroy fails or not return 0
* @precondition			context_trigger_rule_create() for context_trigger_rule_destroy.
* @postcondition		context_trigger_rule_destroy for context_trigger_rule_create
*/
int ITc_context_trigger_rule_create_destroy_p(void)
{
	START_TEST_TRIGGER;

	//Target API
	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Sets and gets the description of a rule
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_set_get_description_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets and gets the description of a rule
* @scenario				Set the description of a rule
*						Get the description of a rule
* @apicovered			context_trigger_rule_set_description, context_trigger_rule_get_description
* @passcase				When context_trigger_rule_set_description and context_trigger_rule_get_description are successful and return 0
* @failcase				If target API context_trigger_rule_set_description and context_trigger_rule_get_description fail or not return 0
* @precondition			context_trigger_rule_create
* @postcondition		context_trigger_rule_destroy
*/
int ITc_context_trigger_rule_set_get_description_p(void)
{
	START_TEST_TRIGGER;

	const char *pszSetDescription = "Set Get Description TC";
	char *pszGetDescription;

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_set_description(g_Handle, pszSetDescription);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_description", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	//Target API
	nRet = context_trigger_rule_get_description(g_Handle, &pszGetDescription);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_get_description", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	if ( strcmp(pszGetDescription, pszSetDescription) != 0 )
	{
		FPRINTF("[Line : %d][%s] Set Get rule description failed, set description and get description are mismatched\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszGetDescription);
		context_trigger_rule_destroy(g_Handle);
		return 1;
	}
	FREE_MEMORY(pszGetDescription);

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Creates an event entry and releases the resource occupied by an entry
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_event_create_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an event entry and releases the resource occupied by an entry
* @scenario				Create an event entry
*						Release the resource occupied by an entry
* @apicovered			context_trigger_rule_event_create, context_trigger_rule_entry_destroy
* @passcase				When context_trigger_rule_event_create and context_trigger_rule_entry_destroy are successful and return 0
* @failcase				If target API context_trigger_rule_event_create or context_trigger_rule_entry_destroy fails or not return 0
* @precondition			context_trigger_rule_event_create for context_trigger_rule_entry_destroy
* @postcondition		NA
*/
int ITc_context_trigger_rule_event_create_destroy_p(void)
{
	START_TEST_TRIGGER;

	int nEnumLoopCount1 =0, nEnumLoopCount2 =0;

	context_trigger_event_e eTriggerEvent[] = {
		CONTEXT_TRIGGER_EVENT_TIME	,
		CONTEXT_TRIGGER_EVENT_BATTERY	,
		CONTEXT_TRIGGER_EVENT_CHARGER,
		CONTEXT_TRIGGER_EVENT_GPS,
		CONTEXT_TRIGGER_EVENT_HEADPHONE,
		CONTEXT_TRIGGER_EVENT_USB,
		CONTEXT_TRIGGER_EVENT_WIFI,
		CONTEXT_TRIGGER_EVENT_POWER_SAVING_MODE	,
		CONTEXT_TRIGGER_EVENT_CALL		,
		CONTEXT_TRIGGER_EVENT_EMAIL,
		CONTEXT_TRIGGER_EVENT_MESSAGE,
		CONTEXT_TRIGGER_EVENT_CONTACTS,
		CONTEXT_TRIGGER_EVENT_PLACE	,
 	};

	context_trigger_logical_type_e eLogicalType[] = {
	CONTEXT_TRIGGER_LOGICAL_CONJUNCTION ,	/**< Logical conjunction */
	CONTEXT_TRIGGER_LOGICAL_DISJUNCTION,		/**< Logical disjunction */
	} ;

	int TriggerLogicalCount = sizeof(eLogicalType) / sizeof(eLogicalType[0]);
	int TriggerEventCount = sizeof(eTriggerEvent) / sizeof(eTriggerEvent[0]);

	for ( nEnumLoopCount1 = 0; nEnumLoopCount1 < TriggerEventCount; nEnumLoopCount1++ )
	{
		// To check if event item is supported on the target
		bool bSupported = true;
		FPRINTF("[Line : %d][%s] Event to be checked on target : %s \\n", __LINE__, API_NAMESPACE, ContextTriggerEvent(eTriggerEvent[nEnumLoopCount1]));
		int nRet = context_trigger_rule_event_is_supported(eTriggerEvent[nEnumLoopCount1], &bSupported);
		PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_is_supported", ContextTriggerGetError(nRet));
		if(bSupported == false)
		{
			FPRINTF("[Line : %d][%s] Event not supported on target : %s \\n", __LINE__, API_NAMESPACE, ContextTriggerEvent(eTriggerEvent[nEnumLoopCount1]));
			continue;
		}

		for ( nEnumLoopCount2 = 0; nEnumLoopCount2 < TriggerLogicalCount; nEnumLoopCount2++ )
		{
			//Target API
			nRet = context_trigger_rule_event_create(eTriggerEvent[nEnumLoopCount1], eLogicalType[nEnumLoopCount2], &g_Event);
			PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

			//Target API
			nRet = context_trigger_rule_entry_destroy(g_Event);
			PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));
			}
	}

	return 0;
}

//& purpose: Creates a condition entry and releases the resource occupied by an entry
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_condition_create_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Creates an condition entry and releases the resource occupied by an entry
* @scenario				Create an condition entry
*						Release the resource occupied by an entry
* @apicovered			context_trigger_rule_condition_create, context_trigger_rule_entry_destroy
* @passcase				When context_trigger_rule_condition_create and context_trigger_rule_entry_destroy are successful and return 0
* @failcase				If target API context_trigger_rule_condition_create or context_trigger_rule_entry_destroy fails or not return 0
* @precondition			context_trigger_rule_condition_create for context_trigger_rule_entry_destroy
* @postcondition		context_trigger_rule_entry_destroy for context_trigger_rule_condition_create
*/
int ITc_context_trigger_rule_condition_create_destroy_p(void)
{
	START_TEST_TRIGGER;
	bool btr_supported = false;

	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_BATTERY, &btr_supported);
	if (!btr_supported) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (Battery)\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	//Target API
	int nRet = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_condition_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_entry_destroy(g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Adds an event or a condition to a rule
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_add_entry_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Adds an event or a condition to a rule
* @scenario				Add an event to a rule\n
*						Add a condition to the rule
* @apicovered			context_trigger_rule_add_entry
* @passcase				When context_trigger_rule_add_entry is successful and return 0
* @failcase				If target API context_trigger_rule_add_entry fails or not return 0
* @precondition			context_trigger_rule_create
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_add_entry_p(void)
{
	START_TEST_TRIGGER;
	bool hdp_supported = false;
	bool btr_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, &hdp_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_BATTERY, &btr_supported);
	if (!(hdp_supported && btr_supported)) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (Headphone %d, Battery %d)\\n", __LINE__, API_NAMESPACE, hdp_supported, btr_supported);
		return 0;
	}


	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Condition);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_condition_create", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_add_key(g_Condition, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "Level");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_add_comparison_string(g_Condition, "Level", "==", "Normal");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_string", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	//Target API
	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	//Target API
	nRet = context_trigger_rule_add_entry(g_Handle, g_Condition);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_destroy(g_Condition);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Adds an attribute key to an entry
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_key_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Adds an attribute key to an entry
* @scenario				Adds an attribute key to an entry
* @apicovered			context_trigger_rule_entry_add_key
* @passcase				When context_trigger_rule_entry_add_key is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_key fails or not return 0
* @precondition			context_trigger_rule_event_create
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_key_p(void)
{
	START_TEST_TRIGGER;

	int nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Adds a comparison between an attribute key and an integer
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_comparison_int_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a comparison between an attribute key and an integer
* @scenario				Add a comparison between an attribute key and an integer
* @apicovered			context_trigger_rule_entry_add_comparison_int
* @passcase				When context_trigger_rule_entry_add_comparison_int is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_comparison_int fails or not return 0
* @precondition			context_trigger_rule_event_create, context_trigger_rule_entry_add_key
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_comparison_int_p(void)
{
	START_TEST_TRIGGER;

	int nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_TIME, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "TimeOfDay");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	//Target API
	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "TimeOfDay", "==", ADD_COMP_INT_VAL);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Adds a comparison between an attribute key and an string.
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_comparison_string_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Adds a comparison between an attribute key and an string
* @scenario				Add a comparison between an attribute key and an string
* @apicovered			context_trigger_rule_entry_add_comparison_string
* @passcase				When context_trigger_rule_entry_add_comparison_string is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_comparison_string fails or not return 0
* @precondition			context_trigger_rule_event_create, context_trigger_rule_entry_add_key
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_comparison_string_p(void)
{
	START_TEST_TRIGGER;
	bool btr_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_BATTERY, &btr_supported);
	if (!btr_supported) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (Battery)\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_BATTERY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "Level");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	//Target API
	nRet = context_trigger_rule_entry_add_comparison_string(g_Event, "Level", "==", "Normal");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_string", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Sets a notification posting request as the action of a rule
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_set_action_notification_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a notification posting request as the action of a rule
* @scenario				Set a notification posting request
* @apicovered			context_trigger_rule_set_action_notification
* @passcase				When context_trigger_rule_set_action_notification is successful and return 0
* @failcase				If target API context_trigger_rule_set_action_notification fails or not return 0
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_rule_entry_add_key
* @postcondition		context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int ITc_context_trigger_rule_set_action_notification_p(void)
{
	START_TEST_TRIGGER;

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	//Target API
	nRet = context_trigger_rule_set_action_notification(g_Handle, "Notification title", "Notification content", NULL, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_notification", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Checks whether a contextual event is supported in the current device
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_event_is_supported_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether a contextual event is supported in the current device
* @scenario				Check if contextual event is supported or not
* @apicovered			context_trigger_rule_event_is_supported
* @passcase				When context_trigger_rule_event_is_supported is successful and return 0
* @failcase				If target API context_trigger_rule_event_is_supported fails or not return 0
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_rule_event_is_supported_p(void)
{
	START_TEST_TRIGGER;

	bool bSupported = false;

	//Target API
	int nRet = context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_HEADPHONE, &bSupported);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_is_supported", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Checks whether a contextual condition is supported in the current device
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_condition_is_supported_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Checks whether a contextual condition is supported in the current device
* @scenario				Check if contextual condition is supported or not
* @apicovered			context_trigger_rule_condition_is_supported
* @passcase				When context_trigger_rule_condition_is_supported is successful and return 0
* @failcase				If target API context_trigger_rule_condition_is_supported fails or not return 0
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_rule_condition_is_supported_p(void)
{
	START_TEST_TRIGGER;

	bool bSupported = false;

	//Target API
	int nRet = context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_HEADPHONE, &bSupported);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_condition_is_supported", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Sets a app launching request as the action of a rule
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_set_action_app_control_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a app launching request as the action of a rule
* @scenario				Set a app launching request as the action of a rule
* @apicovered			context_trigger_rule_set_action_app_control
* @passcase				When context_trigger_rule_set_action_app_control is successful and return 0
* @failcase				If target API context_trigger_rule_set_action_app_control fails or not return 0
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_rule_add_entry
* @postcondition		context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int ITc_context_trigger_rule_set_action_app_control_p(void)
{
	START_TEST_TRIGGER;

	bool bApp = context_initialize_app_handle();
	if ( bApp == false )
	{
		FPRINTF("[Line : %d][%s] context_initialize_app_handle failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet),context_release_app_handle());

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "IsConnected", "==", CONTEXT_TRIGGER_TRUE);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	//Target API
	nRet = context_trigger_rule_set_action_app_control(g_Handle, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose: Using context_trigger_add_rule, application registers a rule and get the ID of the registered rule and context_trigger_remove_rule removes the rule designated by the rule_id, which is owned by the application
//& type: auto
/**
* @testcase 			ITc_context_trigger_add_remove_rule_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Using context_trigger_add_rule, application registers a rule and get the ID of the registered rule and context_trigger_remove_rule removes the rule designated by the rule_id, which is owned by the application
* @scenario				Register a rule\n
*						Removes the rule
* @apicovered			context_trigger_add_rule, context_trigger_remove_rule
* @passcase				When context_trigger_add_rule and context_trigger_remove_rule are successful and return 0
* @failcase				If target API context_trigger_add_rule and context_trigger_remove_rule fail or not return 0
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_rule_entry_add_key, context_trigger_rule_add_entry
* @postcondition		context_trigger_rule_entry_destroy, context_trigger_rule_destroy
 */

int ITc_context_trigger_add_remove_rule_p(void)
{
	START_TEST_TRIGGER;

	int nRuleId = -1;

	bool bApp = context_initialize_app_handle();
	if ( bApp == false )
	{
		FPRINTF("[Line : %d][%s] context_initialize_app_handle failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet),context_release_app_handle());

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "IsConnected", "==", CONTEXT_TRIGGER_TRUE);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_set_action_app_control(g_Handle, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	//Target API
	nRet = context_trigger_add_rule(g_Handle, &nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_add_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());
	if ( nRuleId < 0 )
	{
		FPRINTF("[Line : %d][%s] context_trigger_add_rule failed since rule id assigned is less than zero\\n", __LINE__, API_NAMESPACE);
		context_trigger_rule_entry_destroy(g_Event);
		context_trigger_rule_destroy(g_Handle);
		return 1;
	}

	//Target API
	nRet = context_trigger_remove_rule(nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_remove_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose: Gets a rule stored in the system by rule ID
//& type: auto
/**
* @testcase 			ITc_context_trigger_get_rule_by_id_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets a rule stored in the system by rule ID
* @scenario				Get a rule stored in the system
* @apicovered			context_trigger_get_rule_by_id
* @passcase				When context_trigger_get_rule_by_id is successful and return 0
* @failcase				If target API context_trigger_get_rule_by_id fails or not return 0
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_add_rule
* @postcondition		context_trigger_remove_rule, context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int ITc_context_trigger_get_rule_by_id_p(void)
{
	START_TEST_TRIGGER;

	int nRuleId = -1;
	context_trigger_rule_h ruleResult;

	bool bApp = context_initialize_app_handle();
	if ( bApp == false )
	{
		FPRINTF("[Line : %d][%s] context_initialize_app_handle failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet), context_release_app_handle());

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "IsConnected", "==", CONTEXT_TRIGGER_TRUE);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_set_action_app_control(g_Handle, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_add_rule(g_Handle, &nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_add_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());
	if ( nRuleId < 0 )
	{
		FPRINTF("[Line : %d][%s] context_trigger_add_rule failed since rule id assigned is less than zero\\n", __LINE__, API_NAMESPACE);
		context_trigger_rule_entry_destroy(g_Event);
		context_trigger_rule_destroy(g_Handle);
		context_release_app_handle();
		return 1;
	}

	//Target API
	nRet = context_trigger_get_rule_by_id(nRuleId, &ruleResult);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_get_rule_by_id", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(ruleResult);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_remove_rule(nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_remove_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose:context_trigger_enable_rule activates the rule designated by the rule_id, which is owned by the application context_trigger_disable_rule deactivates the rule designated by the @c rule_id, which is owned by the application
//& type: auto
/**
* @testcase 			ITc_context_trigger_enable_disable_rule_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			context_trigger_enable_rule activates the rule designated by the rule_id, which is owned by the application context_trigger_disable_rule deactivates the rule designated by the @c rule_id, which is owned by the application
* @scenario				Enable a rule\n
*						Disable the rule
* @apicovered			context_trigger_enable_rule, context_trigger_disable_rule
* @passcase				When context_trigger_enable_rule and context_trigger_disable_rule are successful and return 0
* @failcase				If target API context_trigger_enable_rule and context_trigger_disable_rule fail or not return 0
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_add_rule
* @postcondition		context_trigger_remove_rule, context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int ITc_context_trigger_enable_disable_rule_p(void)
{
	START_TEST_TRIGGER;

	int nRuleId = -1;

	bool bApp = context_initialize_app_handle();
	if ( bApp == false )
	{
		FPRINTF("[Line : %d][%s] context_initialize_app_handle failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet),context_release_app_handle());

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "IsConnected", "==", CONTEXT_TRIGGER_TRUE);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_set_action_app_control(g_Handle, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_add_rule(g_Handle, &nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_add_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());
	if ( nRuleId < 0 )
	{
		FPRINTF("[Line : %d][%s] context_trigger_add_rule failed since rule id assigned is less than zero\\n", __LINE__, API_NAMESPACE);
		context_trigger_rule_entry_destroy(g_Event);
		context_trigger_rule_destroy(g_Handle);
		context_release_app_handle();
		return 1;
	}

	//Target API
	nRet = context_trigger_enable_rule(nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_enable_rule", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	//Target API
	nRet = context_trigger_disable_rule(nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_disable_rule", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_remove_rule(nRuleId);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_remove_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose: Gets the IDs of the rules owned by the current application
//& type: auto
/**
* @testcase 			ITc_context_trigger_get_own_rule_ids_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Gets the IDs of the rules owned by the current application
* @scenario				Get the IDs of the rules owned by the current application
* @apicovered			context_trigger_get_own_rule_ids
* @passcase				When context_trigger_get_own_rule_ids is successful and return 0
* @failcase				If target API context_trigger_get_own_rule_ids fails or not return 0
* @precondition			context_trigger_rule_create
* @postcondition		context_trigger_rule_destroy
*/
int ITc_context_trigger_get_own_rule_ids_p(void)
{
	START_TEST_TRIGGER;

	int nRuleId1 = -1;
	int	*pnEnabledArr = NULL;
	int nEnabledCount = 0;
	int *pnDisabledArr = NULL;
	int nDisabledCount = 0;

	bool bApp = context_initialize_app_handle();
	if ( bApp == false )
	{
		FPRINTF("[Line : %d][%s] context_initialize_app_handle failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	int nRet = context_trigger_get_own_rule_ids(&pnEnabledArr, &nEnabledCount, &pnDisabledArr, &nDisabledCount);

	if ( pnEnabledArr )
	{
		free(pnEnabledArr);
		pnEnabledArr = NULL;
	}

	if ( pnDisabledArr )
	{
		free(pnDisabledArr);
		pnDisabledArr = NULL;
	}

	nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet),context_release_app_handle());

	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_add_comparison_int(g_Event, "IsConnected", "==", CONTEXT_TRIGGER_TRUE);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_comparison_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_add_entry(g_Handle, g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_add_entry", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_set_action_app_control(g_Handle, g_AppHandle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_add_rule(g_Handle, &nRuleId1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_add_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	if ( nRuleId1 < 0 )
	{
		FPRINTF("[Line : %d][%s] context_trigger_add_rule failed since rule id assigned is less than zero\\n", __LINE__, API_NAMESPACE);
		context_trigger_rule_entry_destroy(g_Event);
		context_trigger_rule_destroy(g_Handle);
		context_release_app_handle();
		return 1;
	}

	nRet = context_trigger_enable_rule(nRuleId1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_enable_rule", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId1);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	//starting of context_trigger_get_own_rule_id
	//Target API
	nRet = context_trigger_get_own_rule_ids(&pnEnabledArr, &nEnabledCount, &pnDisabledArr, &nDisabledCount);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_get_own_rule_ids", ContextTriggerGetError(nRet), context_trigger_disable_rule(nRuleId1);context_trigger_remove_rule(nRuleId1);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	if ( nEnabledCount != 1 || nDisabledCount != 0 )
	{
		FPRINTF("[Line : %d][%s] context_trigger_get_own_rule_ids failed since, fetched no of enabled and disables rules are not correct\\n", __LINE__, API_NAMESPACE);

		context_trigger_disable_rule(nRuleId1);
		context_trigger_remove_rule(nRuleId1);
		context_trigger_rule_entry_destroy(g_Event);
		context_trigger_rule_destroy(g_Handle);
		context_release_app_handle();

		FREE_MEMORY(pnEnabledArr);
		FREE_MEMORY(pnDisabledArr);
		return 1;
	}

	FREE_MEMORY(pnEnabledArr);
	FREE_MEMORY(pnDisabledArr);
	//end of context_trigger_get_own_rule_ids

	nRet = context_trigger_disable_rule(nRuleId1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_disable_rule", ContextTriggerGetError(nRet), context_trigger_remove_rule(nRuleId1);context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_remove_rule(nRuleId1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_remove_rule", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose: Sets an integer type option to an event or condition entry
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_option_int_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets an integer type option to an event or condition entry
* @scenario				Set an integer type option
* @apicovered			context_trigger_rule_entry_add_option_int
* @passcase				When context_trigger_rule_entry_add_option_int is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_option_int fails or not return 0
* @precondition			context_trigger_rule_condition_create
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_option_int_p(void)
{
	START_TEST_TRIGGER;
	bool place_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_PLACE, &place_supported);
	if (!place_supported) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (Place)\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_PLACE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_entry_add_option_int(g_Event, CONTEXT_TRIGGER_PLACE_ID, ADD_OPTION_INT_VAL);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_option_int", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event));

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Sets a string type option to an event or condition entry
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_option_string_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets an string type option to an event or condition entry
* @scenario				Set an string type option
* @apicovered			context_trigger_rule_entry_add_option_string
* @passcase				When context_trigger_rule_entry_add_option_string is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_option_string fails or not return 0
* @precondition			context_trigger_rule_condition_create
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_option_string_p(void)
{
	START_TEST_TRIGGER;
	bool app_supported = false;

	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, &app_supported);
	if (!app_supported) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (App Use Frequency)\\n", __LINE__, API_NAMESPACE);
		return 0;
	}

	int nRet = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_APP_USE_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_condition_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_entry_add_option_string(g_Condition, CONTEXT_TRIGGER_APP_ID, TEST_TESTAPPLICATION_APPID);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_option_string", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition));

	nRet = context_trigger_rule_entry_destroy(g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Sets an option to a condition entry, which references an attribute that will be extracted from the event
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_entry_add_option_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets an option to a condition entry, which references an attribute that will be extracted from the event
* @scenario				Set an option to a condition entry
* @apicovered			context_trigger_rule_entry_add_option
* @passcase				When context_trigger_rule_entry_add_option is successful and return 0
* @failcase				If target API context_trigger_rule_entry_add_option fails or not return 0
* @precondition			context_trigger_rule_condition_create
* @postcondition		context_trigger_rule_entry_destroy
*/
int ITc_context_trigger_rule_entry_add_option_p(void)
{
	START_TEST_TRIGGER;
	bool call_supported = false;
	bool comm_supported = false;

	context_trigger_rule_event_is_supported(CONTEXT_TRIGGER_EVENT_CALL, &call_supported);
	context_trigger_rule_condition_is_supported(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, &comm_supported);
	if (!(call_supported && comm_supported)) {
		FPRINTF("[Line : %d][%s] Item not supported. Skip test. (Call %d, CommunicationFrequency %d)\\n", __LINE__, API_NAMESPACE, call_supported, comm_supported);
		return 0;
	}

	int nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_CALL, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_condition_create(CONTEXT_TRIGGER_CONDITION_COMMUNICATION_FREQUENCY, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_condition_create", ContextTriggerGetError(nRet));

	//Target API
	nRet = context_trigger_rule_entry_add_option(g_Condition, CONTEXT_TRIGGER_ADDRESS, CONTEXT_TRIGGER_ADDRESS);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_option", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Condition));

	nRet = context_trigger_rule_entry_destroy(g_Condition);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Defines a custom contextual data item with its template and Removes a defined custom contextual data item.
//& type: auto
/**
* @testcase 			ITc_context_trigger_custom_register_unregister_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Defines a custom contextual data item with its template and Removes a defined custom contextual data item.
* @scenario				call context_trigger_custom_register followed by context_trigger_custom_unregister
* @apicovered			context_trigger_custom_register, context_trigger_custom_unregister
* @passcase				When context_trigger_custom_register and context_trigger_custom_unregister is successful and return 0
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_custom_register_unregister_p(void)
{
	START_TEST_TRIGGER;

	int nRet = context_trigger_custom_register(CUSTOM_ITEM_WEATHER,CUSTOM_WEATHER_TEMPLATE);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_register", ContextTriggerGetError(nRet));

	nRet = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_unregister", ContextTriggerGetError(nRet));

	return 0;
}



//& purpose: Publishes an instance of a defined custom contextual data.
//& type: auto
/**
* @testcase 			ITc_context_trigger_custom_publish_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Publishes an instance of a defined custom contextual data.
* @scenario				call context_trigger_custom_publish
* @apicovered			context_trigger_custom_publish
* @passcase				When context_trigger_custom_publish is successful and return 0
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_custom_publish_p(void)
{
	START_TEST_TRIGGER;

	int nRet = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_register", ContextTriggerGetError(nRet));

	nRet = context_trigger_custom_publish(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_DATA1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_publish", ContextTriggerGetError(nRet),context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER));

	nRet = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_unregister", ContextTriggerGetError(nRet));

	return 0;
}

//& purpose: Creates an event entry with custom event, instead of predefined event item #context_trigger_event_e.
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_custom_event_create_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates an event entry with custom event, instead of predefined event item #context_trigger_event_e.
* @scenario				call context_trigger_rule_custom_event_create
* @apicovered			context_trigger_rule_custom_event_create
* @passcase				When context_trigger_rule_custom_event_create is successful and return 0
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_rule_custom_event_create_p(void)
{
	START_TEST_TRIGGER;

	context_trigger_rule_entry_h event1 = NULL;
	context_trigger_rule_entry_h event2 = NULL;

	int nRet = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_register", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &event1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_custom_event_create", ContextTriggerGetError(nRet),context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER));

	nRet = context_trigger_rule_custom_event_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &event2);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_custom_event_create", ContextTriggerGetError(nRet),context_trigger_rule_entry_destroy(event1);context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER));

	nRet = context_trigger_rule_entry_destroy(event1);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_entry_destroy(event2);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	nRet = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_unregister", ContextTriggerGetError(nRet));

	return 0;

}

//& purpose: Creates an event entry with custom event, instead of predefined event item #context_trigger_event_e.
//& type: auto
/**
* @testcase 			ITc_context_trigger_rule_custom_condition_create_p
* @since_tizen 			3.0
* @author				SRID(asit.s)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Creates an event entry with custom event, instead of predefined event item #context_trigger_event_e.
* @scenario				call context_trigger_rule_custom_condition_create
* @apicovered			context_trigger_rule_custom_condition_create
* @passcase				When context_trigger_rule_custom_condition_create is successful and return 0
* @failcase				If target API fails
* @precondition			NA
* @postcondition		NA
*/
int ITc_context_trigger_rule_custom_condition_create_p(void)
{
	START_TEST_TRIGGER;

	context_trigger_rule_entry_h condition1 = NULL;
	context_trigger_rule_entry_h condition2 = NULL;

	int nRet = context_trigger_custom_register(CUSTOM_ITEM_WEATHER, CUSTOM_WEATHER_TEMPLATE);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_register", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &condition1);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_custom_condition_create", ContextTriggerGetError(nRet),context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER));

	nRet = context_trigger_rule_custom_condition_create(CUSTOM_ITEM_WEATHER, CONTEXT_TEST_PACKAGE_ID, CONTEXT_TRIGGER_LOGICAL_DISJUNCTION, &condition2);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_custom_condition_create", ContextTriggerGetError(nRet),context_trigger_rule_entry_destroy(condition1);context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER));

	nRet = context_trigger_rule_entry_destroy(condition1);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	nRet = context_trigger_rule_entry_destroy(condition2);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet));

	nRet = context_trigger_custom_unregister(CUSTOM_ITEM_WEATHER);
	PRINT_RESULT_NORETURN(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_custom_unregister", ContextTriggerGetError(nRet));

	return 0;
}

/** @}*///end of itc-context
/** @}*///end of itc-context-testcases
