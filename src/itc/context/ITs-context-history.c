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

/** @addtogroup itc-context
* @ingroup		itc
* @{
*/

//& set: Context
context_history_h g_Handle;
context_history_filter_h g_filter;
bool g_bContextCreation = false;
context_history_list_h g_history_list;
context_history_record_h g_history_record;

/**
* @function 		ITs_context_history_startup
* @description	 	Called before each test, Check if context history is supported
* @parameter		NA
* @return 			NA
*/
void ITs_context_history_startup(void)
{
	g_bHistoryMismatch = false;
	g_bHistoryNotSupported = false;

	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Context_p\\n", __LINE__, API_NAMESPACE);
#endif
	TCT_CheckInstalledApp(2, TEST_TESTAPPLICATION_APPID, TEST_HELLOWORLD_APPID);

	g_bIsHistoryFeatureSupported = TCTCheckSystemInfoFeatureSupported(HISTORY_FEATURE, API_NAMESPACE);

	bool bSupported;
	int nRet = context_history_is_supported(CONTEXT_HISTORY_RECENTLY_USED_APP, &bSupported);
	if (!g_bIsHistoryFeatureSupported)
	{
		if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED) {
			g_bHistoryNotSupported = true;
		} else {
			g_bHistoryMismatch = true;
		}
	}
}

/**
* @function 		ITs_context_history_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_context_history_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Context_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/** @addtogroup	itc-context-testcases
* @brief 		Integration testcases for module context
* @ingroup		itc-context
* @{
*/

//& purpose: Creates a context history handle and Releases the resources occupied by a handle
//& type: auto
/**
* @testcase 			ITc_context_history_create_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a context history handle and Releases the resources occupied by a handle
* @scenario				Create a context history handle\n
*						Release the resources occupied by a handle
* @apicovered			context_history_create, context_history_destroy
* @passcase				When context_history_create and context_history_destroy are successful and return 0
* @failcase				If target API context_history_create or context_history_destroy fails or not return 0
* @precondition			context_history_create() for context_history_destroy
* @postcondition		NA
*/
int ITc_context_history_create_destroy_p(void)
{
	START_TEST_HISTORY;

	//Target API
	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	//Target API
	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Creates a history filter and Releases the resources occupied by a filter
//& type: auto
/**
* @testcase 			ITc_context_history_filter_create_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Creates a history filter and Releases the resources occupied by a filter
* @scenario				Create a history filter
*						Release the memory allocated for the for the filter
* @apicovered			context_history_filter_create, context_history_filter_destroy
* @passcase				When context_history_filter_create and context_history_filter_destroy are successful and return 0
* @failcase				If target API context_history_filter_create or context_history_filter_destroy fails or return negative value
* @precondition			context_history_filter_create for context_history_filter_destroy.
* @postcondition		NA
*/
int ITc_context_history_filter_create_destroy_p(void)
{
	START_TEST_HISTORY;

	//Target API
	int nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet));

	//Target API
	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Sets an integer value to a filter
//& type: auto
/**
* @testcase 			ITc_context_history_filter_set_int_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			This sets the integer value to a filter
* @scenario				Set an integer value to a filter
* @apicovered			context_history_filter_set_int
* @passcase				If context_history_filter_set_int is successful
* @failcase				If target API context_history_filter_set_int fails
* @precondition			context_history_filter_create must be create
* @postcondition		NA
*/
int ITc_context_history_filter_set_int_p(void)
{
	START_TEST_HISTORY;

	int nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet));

	//Target API
	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE,10);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Sets a string to a filter
//& type: auto
/**
* @testcase 			ITc_context_history_filter_set_string_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Sets a string to a filter
* @scenario				Set the value to a filter
* @apicovered			context_history_filter_set_string
* @passcase				When context_history_filter_set_string are successful and return 0
* @failcase				If target acontext_history_filter_set_string fails or return negative number
* @precondition			context_history_filter_create must be create.
* @postcondition		NA
*/
int ITc_context_history_filter_set_string_p(void)
{
	START_TEST_HISTORY;

	int nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet));
#if defined  (MOBILE ) || defined  (TIZENIOT)
	//Target API
	nRet = context_history_filter_set_string(g_filter, CONTEXT_HISTORY_FILTER_APP_ID, TEST_TESTAPPLICATION_APPID);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_string", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter));
#endif	//MOBILE OR TIZENIOT
	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Reads context statistics or patterns Destroy handle and releases all its resources
//& type: auto
/**
* @testcase 			ITc_context_history_get_list_destroy_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves a given type of context statistics or patterns list Destroy handle and releases all its resources
* @scenario				Read context statistics or patterns
*						Destroy handle and releases all its resources
* @apicovered			context_history_get_list and context_history_list_destroy
* @passcase				When context_history_get_list and context_history_list_destroy are successful and return 0
* @failcase				If target API context_history_get_list and context_history_list_destroy fail and return negative number
* @precondition			context_history_create and context_history_filter_create
* @postcondition		context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int ITc_context_history_get_list_destroy_p(void)
{
	START_TEST_HISTORY;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN,INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE,INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Retrieves the number of records in a list
//& type: auto
/**
* @testcase 			ITc_context_history_list_get_count_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the number of records in a list
* @scenario				Count number of records in a list
* @apicovered			context_history_list_get_count
* @passcase				When context_history_list_get_count execute successfully and return 0
* @failcase				If target API context_history_list_get_count fails and return negative number
* @precondition			context_history_create, context_history_filter_create, context_history_get_list
* @postcondition		context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int ITc_context_history_list_get_count_p(void)
{
	START_TEST_HISTORY;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nListCount;

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN,INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_list_get_count(g_history_list, &nListCount);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_get_count", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Retrieves the current record from the history list
//& type: auto
/**
* @testcase 			ITc_context_history_list_get_current_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves the current record from the history list
* @scenario				Read current record
* @apicovered			context_history_list_get_current
* @passcase				When context_history_list_get_current is successful and return 0
* @failcase				If target API context_history_list_get_current fails and return negative number
* @precondition			context_history_create and context_history_filter_create, context_history_get_list
* @postcondition		context_history_record_destroy, context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int ITc_context_history_list_get_current_p(void)
{
	START_TEST_HISTORY;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_list_get_current(g_history_list, &g_history_record);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_get_current", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_record_destroy(g_history_record);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_record_destroy", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Moves a history data list to the first position
//& type: auto
/**
* @testcase 			ITc_context_history_list_move_first_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Retrieves a given type of context statistics or patterns list
* @scenario				Read context statistics or patterns
* @apicovered			context_history_list_move_first
* @passcase				When context_history_list_move_first is successful and return 0
* @failcase				If target API context_history_list_move_first fails and return negative number
* @precondition			context_history_create and context_history_filter_create, context_history_get_list
* @postcondition		context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int ITc_context_history_list_move_first_p(void)
{
	START_TEST_HISTORY;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_list_move_first(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_move_first", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Moves a history data list to the next position
//& type: auto
/**
* @testcase 			ITc_context_history_list_move_next_p
* @since_tizen 			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Moves a history data list to the next position
* @scenario				Move a history data list to the next position
* @apicovered			context_history_list_move_next
* @passcase				When context_history_list_move_next is successful and return 0
* @failcase				If target API context_history_list_move_next fails and return negative number
* @precondition			context_history_create and context_history_filter_create, context_history_get_list
* @postcondition		context_history_list_destroy, context_history_filter_destroy, context_history_destroy
*/
int ITc_context_history_list_move_next_p(void)
{
	START_TEST_HISTORY;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL2);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
		context_history_filter_destroy(g_filter);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_list_move_next(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_move_next", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_filter_destroy(g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

//& purpose: Gets an integer and a string values from the record
//& type: auto
/**
* @testcase				ITc_context_history_record_get_int_string_p
* @since_tizen			2.4
* @author				SRID(ajay.kr1)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Gets an integer and a string values from the record
* @scenario				Get a record from a list retrieved\n
*						Get an integer and a string values from the record
* @apicovered			context_history_record_get_int and context_history_record_get_string
* @passcase				When context_history_record_get_int and context_history_record_get_string are successful and return 0
* @failcase				If context_history_record_get_int or context_history_record_get_string fail and return negative number
* @precondition			context_history_create, context_history_get_list, context_history_list_get_current
* @postcondition		context_history_list_destroy, context_history_record_destroy, context_history_destroy
*/
int ITc_context_history_record_get_int_string_p(void)
{
	START_TEST_HISTORY;

	int nValue = -1;
	char *sValue = NULL;

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_RECENTLY_USED_APP, NULL, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_RECENTLY_USED_APP. Data not exist.\\n", __LINE__, API_NAMESPACE);
		context_history_destroy(g_Handle);
		return 0;
	}
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_list_get_current(g_history_list, &g_history_record);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_get_current", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_destroy(g_Handle));

	//Target API
	nRet = context_history_record_get_int(g_history_record, CONTEXT_HISTORY_TOTAL_COUNT, &nValue);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_record_get_int", ContextHistoryGetError(nRet), context_history_record_destroy(g_history_record);context_history_list_destroy(g_history_list);context_history_destroy(g_Handle));

	if (nValue < 0)
	{
		FPRINTF("[Line : %d][%s] context_history_record_get_int failed, CONTEXT_HISTORY_TOTAL_COUNT should be greater than or equal to 0\\n", __LINE__, API_NAMESPACE);
		context_history_record_destroy(g_history_record);
		context_history_list_destroy(g_history_list);
		context_history_destroy(g_Handle);
		return 1;
	}

	//Target API
	nRet = context_history_record_get_string(g_history_record, CONTEXT_HISTORY_APP_ID, &sValue);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_record_get_string", ContextHistoryGetError(nRet), context_history_record_destroy(g_history_record);context_history_list_destroy(g_history_list);context_history_destroy(g_Handle));

	if (sValue == NULL || strlen(sValue) == 0)
	{
		FPRINTF("[Line : %d][%s] context_history_record_get_string failed, CONTEXT_HISTORY_APP_ID should not be an empty string\\n", __LINE__, API_NAMESPACE);
		context_history_record_destroy(g_history_record);
		context_history_list_destroy(g_history_list);
		context_history_destroy(g_Handle);
		return 1;
	}

	nRet = context_history_record_destroy(g_history_record);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_record_destroy", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_destroy(g_Handle));

	nRet = context_history_list_destroy(g_history_list);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_destroy", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));

	nRet = context_history_destroy(g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_destroy", ContextHistoryGetError(nRet));

	return 0;
}

#if defined  (MOBILE ) || defined  (TIZENIOT)
//& purpose: Get a double value from the record
//& type: auto
/**
* @testcase				ITc_context_history_record_get_double_p
* @since_tizen			3.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			Get a double value from the record
* @scenario				Get a record from a list retrieved\n
*						Get an double value from the record
* @apicovered			context_history_record_get_double
* @passcase				When context_history_record_get_double is successful and return 0
* @failcase				If context_history_record_get_double fail and return negative number
* @precondition			context_history_create, context_history_get_list, context_history_list_get_current
* @postcondition		context_history_list_destroy, context_history_record_destroy, context_history_destroy
*/
int ITc_context_history_record_get_double_p(void)
{
	START_TEST_HISTORY;

	double nValue;

	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));
	CHECK_HANDLE(g_Handle,"context_history_create");

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));
	CHECK_HANDLE_CLEANUP(g_filter,"context_history_filter_create",context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_TIME_SPAN, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	nRet = context_history_get_list(g_Handle, CONTEXT_HISTORY_BATTERY_USAGE, g_filter, &g_history_list);
	if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
	{
		FPRINTF("[Line : %d][%s] Skip context_history_get_list() for CONTEXT_HISTORY_BATTERY_USAGE. Data not exist.\\n", __LINE__, API_NAMESPACE);
	}
	else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED && !bFeatureIsSupported)
	{
		FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
	}
	else
	{
		PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));
		CHECK_HANDLE_CLEANUP(g_history_list,"context_history_get_list",context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

		nRet = context_history_list_get_current(g_history_list, &g_history_record);
		PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_list_get_current", ContextHistoryGetError(nRet), context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));
		CHECK_HANDLE_CLEANUP(g_history_record,"context_history_list_get_current",context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

		//Target API
		nRet = context_history_record_get_double(g_history_record, CONTEXT_HISTORY_TOTAL_AMOUNT, &nValue);
		PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_record_get_double", ContextHistoryGetError(nRet), context_history_record_destroy(g_history_record);context_history_list_destroy(g_history_list);context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

		if (nValue < 0)
		{
			FPRINTF("[Line : %d][%s] context_history_record_get_double failed, CONTEXT_HISTORY_TOTAL_COUNT should be greater than or equal to 0\\n", __LINE__, API_NAMESPACE);
			context_history_record_destroy(g_history_record);
			context_history_list_destroy(g_history_list);
			context_history_filter_destroy(g_filter);
			context_history_destroy(g_Handle);
			return 1;
		}
		context_history_record_destroy(g_history_record);
		context_history_list_destroy(g_history_list);
	}
	context_history_filter_destroy(g_filter);
	context_history_destroy(g_Handle);
	return 0;
}
#endif	//MOBILE OR TIZENIOT
//& purpose: Retrieves a given type of context statistics or patterns list
//& type: auto
/**
* @testcase				ITc_context_history_get_list_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			Retrieves a given type of context statistics or patterns list
* @scenario				Retrieves a given type of context statistics or patterns list
* @apicovered			context_history_get_list
* @passcase				When context_history_get_list is successful and return 0
* @failcase				If context_history_get_list fail and return negative number
* @precondition			context_history_create
* @postcondition		context_history_destroy
*/
int ITc_context_history_get_list_p(void)
{
	START_TEST_HISTORY;

	context_history_data_e eContextHistory[]={
							CONTEXT_HISTORY_RECENTLY_USED_APP,
							CONTEXT_HISTORY_FREQUENTLY_USED_APP,
							CONTEXT_HISTORY_BATTERY_USAGE,
							CONTEXT_HISTORY_RECENT_BATTERY_USAGE
							};
	int nEnumLength = sizeof(eContextHistory)/sizeof(eContextHistory[0]);
	bool bFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(BATTERY_FEATURE, API_NAMESPACE);

	int nRet = context_history_create(&g_Handle);
	PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_create", ContextHistoryGetError(nRet));
	CHECK_HANDLE(g_Handle,"context_history_create");

	nRet = context_history_filter_create(&g_filter);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_create", ContextHistoryGetError(nRet), context_history_destroy(g_Handle));
	CHECK_HANDLE_CLEANUP(g_filter,"context_history_filter_create",context_history_destroy(g_Handle));

	nRet = context_history_filter_set_int(g_filter, CONTEXT_HISTORY_FILTER_RESULT_SIZE, INT_VAL1);
	PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_filter_set_int", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));

	for(int nLoopEnumCount = 0; nLoopEnumCount < nEnumLength; nLoopEnumCount++)
	{
		nRet = context_history_get_list(g_Handle, eContextHistory[nLoopEnumCount], g_filter, &g_history_list);
		if (nRet == CONTEXT_HISTORY_ERROR_NO_DATA)
		{
			FPRINTF("[Line : %d][%s] Skip context_history_get_list() for %s. Data not exist.\\n", __LINE__, API_NAMESPACE,ContextHistoryGetHistoryData(eContextHistory[nLoopEnumCount]));
			continue;
		}
		else if (nRet == CONTEXT_HISTORY_ERROR_NOT_SUPPORTED)
		{
			if(eContextHistory[nLoopEnumCount] == CONTEXT_HISTORY_BATTERY_USAGE || eContextHistory[nLoopEnumCount] == CONTEXT_HISTORY_RECENT_BATTERY_USAGE)
			{
				if(!bFeatureIsSupported)
				{
					FPRINTF("[Line : %d][%s] Feature Not Supported for api context_history_get_list\\n", __LINE__, API_NAMESPACE);
					continue;
				}
			}
		}

		PRINT_RESULT_CLEANUP(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_get_list", ContextHistoryGetError(nRet), context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));
		CHECK_HANDLE_CLEANUP(g_history_list,"context_history_get_list",context_history_filter_destroy(g_filter);context_history_destroy(g_Handle));
		context_history_list_destroy(g_history_list);
	}
	context_history_filter_destroy(g_filter);
	context_history_destroy(g_Handle);

	return 0;
}
#if defined  (MOBILE ) || defined  (TIZENIOT)
//& purpose:   Checks whether a history data type is supported in the current device.
//& type: auto
/**
* @testcase				ITc_context_history_is_supported_p
* @since_tizen			4.0
* @author				SRID(nibha.sharma)
* @reviewer				SRID(a.pandia1)
* @type					auto
* @description			Checks whether a history data type is supported in the current device.
* @scenario				Checks whether a history data type is supported in the current device.
* @apicovered			context_history_is_supported
* @passcase				When context_history_is_supported is successful and return 0
* @failcase				If context_history_is_supported fail and return negative number
* @precondition			na
* @postcondition		na
*/
int ITc_context_history_is_supported_p(void)
{
	START_TEST_HISTORY;

	context_history_data_e eContextHistory[]={
							CONTEXT_HISTORY_RECENTLY_USED_APP,
							CONTEXT_HISTORY_FREQUENTLY_USED_APP,
							CONTEXT_HISTORY_BATTERY_USAGE,
							CONTEXT_HISTORY_RECENT_BATTERY_USAGE
							};

	bool bIsSupported;
	int nEnumLength = sizeof(eContextHistory)/sizeof(eContextHistory[0]);
	for(int nLoopEnumCount = 0; nLoopEnumCount < nEnumLength; nLoopEnumCount++)
	{
		int nRet = context_history_is_supported(eContextHistory[nLoopEnumCount], &bIsSupported);
		PRINT_RESULT(CONTEXT_HISTORY_ERROR_NONE, nRet, "context_history_is_supported", ContextHistoryGetError(nRet));
		if(bIsSupported == false)
		{
			FPRINTF("[Line : %d][%s] bIsSupported is false for context history data %s\\n", __LINE__, API_NAMESPACE,ContextHistoryGetHistoryData(eContextHistory[nLoopEnumCount]));
		}
		else
		{
			FPRINTF("[Line : %d][%s] bIsSupported is true for context history data %s\\n", __LINE__, API_NAMESPACE,ContextHistoryGetHistoryData(eContextHistory[nLoopEnumCount]));
		}
	}

	return 0;
}

#endif	//MOBILE OR TIZENIOT
/** @}*///end of itc-context
/** @}*///end of itc-context-testcases
