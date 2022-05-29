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
#include "ITs-data-control-common.h"

/** @addtogroup itc-data-control
*  @ingroup itc
*  @{
*/

//& set: DataControl
/*******************************************************************************CallBack Functions********************************************************/

/**
* @function 		DataControlMapAddResponseCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapAddResponseCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlMapAddResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Insert operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Insert operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
	}

	if(strcmp((char*)user_data,TESTSTRING) != 0)
	{
		FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlMapRemoveResponseCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapRemoveResponseCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlMapRemoveResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Delete operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Delete operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
	}

	if(strcmp((char*)user_data,TESTSTRING) != 0)
	{
		FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlMapSetResponseCb
* @description	 	Called when record is changed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapSetResponseCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlMapSetResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Set operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Set operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
	}

	if(strcmp((char*)user_data,TESTSTRING) != 0)
	{
		FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlMapGetResponseCb
* @description	 	Called when record is retrieved
* @parameter		int request_id, data_control_h provider, char ** result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapGetResponseCb(int request_id, data_control_h provider, char ** result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data)
{
	int nCount = 0;
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlMapGetResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Get operation successful\\n", __LINE__, API_NAMESPACE);
		while ( (result_value_count > 0 ) && (nCount < result_value_count) && (!g_bCallbackHit) )
		{
			if (g_bIsInsertDataCheck)
			{
				if ( strncmp(result_value_list[nCount], DUMMYVALUE, strlen(result_value_list[nCount])) == 0 )
				{
					FPRINTF("[Line : %d][%s] Get operation after Add operation('TestValue') is successful\\n", __LINE__, API_NAMESPACE);
					g_bCallbackHit = true;
				}
			}
			else if ( strncmp(result_value_list[nCount], DUMMYVALUENEW, strlen(result_value_list[nCount])) == 0 )
			{
				FPRINTF("[Line : %d][%s] Get operation after Set operation('TestValueNew') is successful\\n", __LINE__, API_NAMESPACE);
				g_bCallbackHit = true;
			}
			nCount++;
		}
		if ( !g_bCallbackHit )
		{
			FPRINTF("[Line : %d][%s] Set operation failed, no value found which was previously set : %s\\n", __LINE__, API_NAMESPACE, DUMMYVALUENEW);
		}
	}
	else 
	{
		if (g_bIsRemoveDataCheck)
		{
			FPRINTF("[Line : %d][%s] Get operation after Remove operation is successful\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = true;
		}
		else
		{
			FPRINTF("[Line : %d][%s] Get operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		}
	}

	if(strcmp((char*)user_data, TESTSTRING) != 0)
	{
		FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlMapGetWithPageResponseCb
* @description	 	Called when record is retrieved
* @parameter		int request_id, data_control_h provider, char ** result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapGetWithPageResponseCb(int request_id, data_control_h provider, char ** result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlMapGetWithPageResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Get operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Get operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
	}

	if(strcmp((char*)user_data,TESTSTRING) != 0)
	{
		FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = false;
	}
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/***************************************************************************End CallBack Functions********************************************************/

/**
* @function 		ITs_data_control_map_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_map_startup(void)
{
	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_DATACONTROL_APPID);
	g_bDataControlCreation = false;
	if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
	{
		g_bDataControlCreation = true;
	}
}

/**
* @function 		ITs_data_control_map_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_map_cleanup(void)
{
	if ( g_bDataControlCreation == true )
	{
		data_control_map_destroy(g_stMapProvider);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/** @addtogroup itc-data-control-map-testcases
*  @brief 		Integration testcases for module data-control-map
*  @ingroup 	itc-data-control-map
*  @{
*/

/**
* @testcase 			ITc_data_control_map_data_control_map_destroy_create_p
* @since_tizen			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_map_destroy and data_control_map_create
* @scenario				Call data_control_map_destroy\n
*						Call data_control_map_create
* @apicovered			data_control_map_destroy, data_control_map_create
* @passcase				When data_control_map_destroy and data_control_map_create are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_destroy and data_control_map_create
//& type: auto
int ITc_data_control_map_data_control_map_destroy_create_p(void)
{
	START_TEST;

	// Target API
	int nRet = data_control_map_destroy(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_destroy", DataControlGetError(nRet));
	g_bDataControlCreation = false;
	// Target API
	nRet = data_control_map_create(&g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));
	if(g_stMapProvider == NULL)
	{
		FPRINTF("[Line : %d][%s] data_control_map_create failed, error = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;		
	}
	g_bDataControlCreation = true;
	return 0;
}

/**
* @testcase 			ITc_data_control_map_data_control_map_set_get_data_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_map_set_data_id and data_control_map_get_data_id
* @scenario				Call data_control_map_set_data_id\n
*						Call data_control_map_get_data_id
* @apicovered			data_control_map_set_data_id, data_control_map_get_data_id
* @passcase				When data_control_map_set_data_id and data_control_map_get_data_id are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_set_data_id and data_control_map_get_data_id
//& type: auto
int ITc_data_control_map_data_control_map_set_get_data_id_p(void)
{
	START_TEST;

	// Target API
	int nRet = data_control_map_set_data_id(g_stMapProvider, MAPDATAID);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet));

	// Target API
	char *pszDataId = NULL;
	nRet = data_control_map_get_data_id(g_stMapProvider, &pszDataId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_data_id", DataControlGetError(nRet));

	if ( strstr(pszDataId, MAPDATAID) == NULL )
	{
		FPRINTF("[Line : %d][%s] data_control_map_get_data_id failed as Data Id not found\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDataId);
		return 1;
	}
	FREE_MEMORY(pszDataId);
	return 0;
}


/**
* @testcase 			ITc_data_control_map_data_control_map_set_get_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Set and get a DB entry
* @scenario				Set Entry\n
*						Get Entry
* @apicovered			data_control_map_set, data_control_map_get 
* @passcase				When data_control_map_set and data_control_map_get are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_set and data_control_map_get 
//& type: auto
int ITc_data_control_map_data_control_map_set_get_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	const char *pszKey = DUMMYKEY;
	const char *pszValue = DUMMYVALUE;
	const char *pszNewValue = DUMMYVALUENEW;

	data_control_map_response_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlMapAddResponseCb;
	stMapCallBack.remove_cb = DataControlMapRemoveResponseCb;
	stMapCallBack.set_cb = DataControlMapSetResponseCb;
	stMapCallBack.get_cb = DataControlMapGetResponseCb;

	int nRet = data_control_map_register_response_cb(g_stMapProvider, &stMapCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_register_response_cb", DataControlGetError(nRet));

	g_bCallbackHit = false;
	
	nRet = data_control_map_add(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}
	
	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;

	nRet = data_control_map_get(g_stMapProvider, DUMMYKEY, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to get value from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;

	// Target API
	nRet = data_control_map_set(g_stMapProvider, pszKey, pszValue, pszNewValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to set data, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}
		
	g_bCallbackHit = false;
	g_bIsInsertDataCheck = false; // Check DUMMYVALUENEW

	// Target API
	nRet = data_control_map_get(g_stMapProvider, DUMMYKEY, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to get value from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;
	
	nRet = data_control_map_remove(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_remove", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to remove form DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	nRet = data_control_map_unregister_response_cb(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_data_control_map_data_control_map_set_get_provider_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_map_set_provider_id and data_control_map_get_provider_id
* @scenario				Call data_control_map_set_provider_id\n
*						Call data_control_map_get_provider_id
* @apicovered			data_control_map_set_provider_id, data_control_map_get_provider_id
* @passcase				When data_control_map_set_provider_id and data_control_map_get_provider_id are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_set_provider_id and data_control_map_get_provider_id
//& type: auto
int ITc_data_control_map_data_control_map_set_get_provider_id_p(void)
{
	START_TEST;

	// Target API
	int nRet = data_control_map_set_provider_id(g_stMapProvider, MAPPROVIDERID);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet));

	// Target API
	char *pszDataId = NULL;
	nRet = data_control_map_get_provider_id(g_stMapProvider, &pszDataId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_provider_id", DataControlGetError(nRet));

	if ( strstr(pszDataId, MAPPROVIDERID) == NULL )
	{
		FPRINTF("[Line : %d][%s] data_control_map_get_provider_id failed as Data Id not found\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDataId);
		return 1;
	}
	FREE_MEMORY(pszDataId);
	return 0;
}

/**
* @testcase 			ITc_data_control_map_data_control_map_register_unregister_response_cb_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_map_register_response_cb and data_control_map_unregister_response_cb
* @scenario				Call data_control_map_register_response_cb\n
*						Call data_control_map_unregister_response_cb
* @apicovered			data_control_map_register_response_cb, data_control_map_unregister_response_cb
* @passcase				When data_control_map_register_response_cb and data_control_map_unregister_response_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_register_response_cb and data_control_map_unregister_response_cb
//& type: auto
int ITc_data_control_map_data_control_map_register_unregister_response_cb_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	const char *pszKey = DUMMYKEY;
	const char *pszValue = DUMMYVALUE;
	data_control_map_response_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlMapAddResponseCb;
	stMapCallBack.remove_cb = DataControlMapRemoveResponseCb;
	stMapCallBack.get_cb = DataControlMapGetWithPageResponseCb;

	// Target API
	int nRet = data_control_map_register_response_cb(g_stMapProvider, &stMapCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_register_response_cb", DataControlGetError(nRet));

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	
	nRet = data_control_map_add(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;
	g_bIsRemoveDataCheck = false;
	nRet = data_control_map_remove(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_remove", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to remove form DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	// Target API
	nRet = data_control_map_unregister_response_cb(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_map_data_control_map_add_remove_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Insert and delete a DB entry
* @scenario				Insert Entry\n
*						Delete Entry
* @apicovered			data_control_map_add, data_control_map_remove
* @passcase				When data_control_map_add and data_control_map_remove are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_add and data_control_map_remove
//& type: auto
int ITc_data_control_map_data_control_map_add_remove_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	const char *pszKey = DUMMYKEY;
	const char *pszValue = DUMMYVALUE;

	data_control_map_response_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlMapAddResponseCb;
	stMapCallBack.remove_cb = DataControlMapRemoveResponseCb;
	stMapCallBack.get_cb = DataControlMapGetResponseCb;

	int nRet = data_control_map_register_response_cb(g_stMapProvider, &stMapCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_register_response_cb", DataControlGetError(nRet));

	g_bCallbackHit = false;

	// Target API
	nRet = data_control_map_add(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;

	nRet = data_control_map_get(g_stMapProvider, DUMMYKEY, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to get value from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;

	// Target API
	nRet = data_control_map_remove(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_remove", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to remove form DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;
	g_bIsRemoveDataCheck = true;

	// Target API
	nRet = data_control_map_get(g_stMapProvider, DUMMYKEY, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;

	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to get value from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	nRet = data_control_map_unregister_response_cb(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_map_data_control_map_get_with_page_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Get a DB entry
* @scenario				Get Entry
* @apicovered			data_control_map_get_with_page
* @passcase				When data_control_map_get_with_page is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_map_get_with_page
//& type: auto
int ITc_data_control_map_data_control_map_get_with_page_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;
	const char *pszKey = DUMMYKEY;
	const char *pszValue = DUMMYVALUE;

	data_control_map_response_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlMapAddResponseCb;
	stMapCallBack.remove_cb = DataControlMapRemoveResponseCb;
	stMapCallBack.get_cb = DataControlMapGetWithPageResponseCb;

	int nRet = data_control_map_register_response_cb(g_stMapProvider, &stMapCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_register_response_cb", DataControlGetError(nRet));

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	
	nRet = data_control_map_add(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;

	// Target API
	nRet = data_control_map_get_with_page(g_stMapProvider, pszKey, &nRequestId, 1, 1);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_with_page", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to get data, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	g_bCallbackHit = false;
	nRet = data_control_map_remove(g_stMapProvider, pszKey, pszValue, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_remove", DataControlGetError(nRet), data_control_map_unregister_response_cb(g_stMapProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to remove form DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_map_unregister_response_cb(g_stMapProvider);
		return 1;
	}

	nRet = data_control_map_unregister_response_cb(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}
/** @} */
/** @} */