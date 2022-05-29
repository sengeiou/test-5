#include "context_history.h"
#include "context_trigger.h"
#include "CTs-platform-permission-common.h"

context_history_h g_Handle= NULL;
context_history_filter_h g_filter= NULL;
bool g_bContextCreation = false;
context_history_list_h g_history_list= NULL;
app_control_h g_AppHandle= NULL;
context_trigger_rule_h g_THandle= NULL;
context_trigger_rule_entry_h g_Event = NULL;
context_history_record_h g_history_record= NULL;

#define INT_VAL1			30
#define INT_VAL2			10

#define APP_ID				"org.tizen.testapplication"

/**
* @function 		CTs_platform_permission_context_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_context_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		if (remove(ERR_LOG))
		{
			FPRINTF("[Line : %d][%s] TEST SUIT start-up FAIL because the ERR_LOG file is not removed\\n", __LINE__, API_NAMESPACE);
		}
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(5, TPK1, TPK2, TPK3, TPK4, TPK5);
}

/**
* @function 		CTs_platform_permission_context_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_context_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}
/**
* @function 		ContextHistoryGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
/*char* ContextHistoryGetError(int nRet)
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
}*/

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
		default:
			pszErrorVal = "Unknown Error";
			break;
	}

	return pszErrorVal;
}

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

	nRet = app_control_set_app_id (g_AppHandle, APP_ID);
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

//& purpose: Reads context statistics or patterns Destroy handle and releases all its resources
//& type: auto
/**
* @testcase 			CTc_Context_PrivilegeApphistoryRead_PrivilegeMediahistoryRead
* @since_tizen 			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Retrieves a given type of context statistics or patterns list Destroy handle and releases all its resources
* @scenario				Read context statistics or patterns
*						Destroy handle and releases all its resources
* @apicovered			context_history_get_list and context_history_list_destroy
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			context_history_create and context_history_filter_create
* @postcondition		context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int CTc_Context_PrivilegeApphistoryRead_PrivilegeMediahistoryRead(void)
{
	START_TEST;

	int nRet;

	nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));
	
	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));
 
	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_RARELY_USED_APP, g_filter, &g_history_list);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle);context_history_list_destroy(g_history_list));
	
	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

/**
* @function 		release_app_handle
* @description	 	Destroy an app handle
* @parameter		NA
* @return 			NA
*/
void release_app_handle(void)
{
	app_control_destroy(g_AppHandle);
}


//& purpose: Sets a app launching request as the action of a rule
//& type: auto 
/**
* @testcase 			CTc_Context_PrivilegeAppManagerLaunch_PrivilegeCall_set_action
* @since_tizen 			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets a app launching request as the action of a rule
* @scenario				Set a app launching request as the action of a rule
* @apicovered			context_trigger_rule_set_action_app_control,context_trigger_add_rule
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_rule_add_entry
* @postcondition		context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int CTc_Context_PrivilegeAppManagerLaunch_PrivilegeCall_set_action(void)
{
	
	START_TEST;
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if (!g_bIsSupported)
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_WIFI, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_WIFI);
		return 0;
		
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if( !g_bIsSupported ) 
	{	
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_GPS, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_GPS);
		return 0;
	}
	
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
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "context_trigger_rule_set_action_app_control", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle);context_release_app_handle());

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet),context_release_app_handle());

	context_release_app_handle();

	return 0;
}

//& purpose: Sets a notification posting request as the action of a rule
//& type: auto 
/**
* @testcase 			CTc_Context_PrivilegeNotification
* @since_tizen 			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sets a notification posting request as the action of a rule
* @scenario				Set a notification posting request
* @apicovered			context_trigger_rule_set_action_notification
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			context_trigger_rule_create, context_trigger_rule_event_create, context_trigger_rule_entry_add_key
* @postcondition		context_trigger_rule_entry_destroy, context_trigger_rule_destroy
*/
int CTc_Context_PrivilegeNotification(void)
{
	START_TEST;
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_TELEPHONY, g_bIsSupported, API_NAMESPACE);
	if (!g_bIsSupported)
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_TELEPHONY);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_NETWORK_WIFI, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_NETWORK_WIFI);
		return 0;
		
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_BLUETOOTH, g_bIsSupported, API_NAMESPACE);
	if( !g_bIsSupported ) 
	{	
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_BLUETOOTH);
		return 0;
	}
	
	g_bIsSupported = false;
	IS_FEATURE_SUPPORTED(FEATURE_GPS, g_bIsSupported, API_NAMESPACE);
	if ( !g_bIsSupported )
	{
		FPRINTF("[Line : %d][%s] [%s] is not supported\\n", __LINE__, API_NAMESPACE, FEATURE_GPS);
		return 0;
	}
	
	int nRet = context_trigger_rule_create(CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_create", ContextTriggerGetError(nRet));
	
	nRet = context_trigger_rule_event_create(CONTEXT_TRIGGER_EVENT_HEADPHONE, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, &g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_event_create", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));
	
	nRet = context_trigger_rule_entry_add_key(g_Event, CONTEXT_TRIGGER_LOGICAL_CONJUNCTION, "IsConnected");
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_add_key", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));

	//Target API
	nRet = context_trigger_rule_set_action_notification(g_Handle, "Notification title", "Notification content", NULL, g_AppHandle);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "context_trigger_rule_set_action_notification", ContextTriggerGetError(nRet), context_trigger_rule_entry_destroy(g_Event);context_trigger_rule_destroy(g_Handle));
	
	nRet = context_trigger_rule_entry_destroy(g_Event);
	PRINT_RESULT_CLEANUP(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_entry_destroy", ContextTriggerGetError(nRet), context_trigger_rule_destroy(g_Handle));

	nRet = context_trigger_rule_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_TRIGGER_ERROR_NONE, nRet, "context_trigger_rule_destroy", ContextTriggerGetError(nRet));

	return 0;
}
