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
* @function 		ChangeNotiConsumerListCB
* @description	 	Called when received data changed notification from provider application.
* @parameter		data_control_h provider, char *consumer_appid, void *user_data
* @return 			NA
*/
bool ChangeNotiConsumerListCB(data_control_h provider, char *consumer_appid, void *user_data)
{

#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlDataChangeCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
FPRINTF("[Line : %d][%s] DataControlDataChangeCB callback called\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;

	return true;
}
/**
* @function 		DataControlProviderDataChangeConsumerFilterCB
* @description	 	Called when a consumer requests a data change callback addition.
* @parameter		data_control_h provider, char *consumer_appid, void *user_data
* @return 			NA
*/
static bool DataControlProviderDataChangeConsumerFilterCB( data_control_h provider, char *consumer_appid, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlProviderDataChangeConsumerFilterCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
FPRINTF("[Line : %d][%s] DataControlProviderDataChangeConsumerFilterCB callback called\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;

	return true;
}

/**
* @function 		DataControlProviderSqlInsertCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, bundle *insert_data, void *user_data
* @return 			NA
*/
static void DataControlProviderSqlInsertCb(int request_id, data_control_h provider, bundle *insert_data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlProviderSqlInsertCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	g_nRequestId = request_id;
	g_bCallbackHit = true;

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
* @function 		DataControlProviderSqlRemoveCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, const char *where, void *user_data
* @return 			NA
*/
static void DataControlProviderSqlRemoveCb(int request_id, data_control_h provider, const char *where, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlProviderSqlRemoveCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	g_nRequestId = request_id;
	g_bCallbackHit = true;

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
* @function 		DataControlProviderMapInsertCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, const char *key, const char *value, void *user_data
* @return 			NA
*/
static void DataControlProviderMapInsertCb(int request_id, data_control_h provider, const char *key, const char *value, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlProviderMapInsertCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	g_nRequestId = request_id;
	g_bCallbackHit = true;

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
* @function 		DataControlProviderMapRemoveCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, const char *key, const char *value, void *user_data
* @return 			NA
*/
static void DataControlProviderMapRemoveCb(int request_id, data_control_h provider, const char *key, const char *value, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlProviderMapRemoveCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	g_nRequestId = request_id;
	g_bCallbackHit = true;

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
static void InsertRequestCB(int request_id, data_control_h provider, bundle *insert_data, void *user_data)
{
}

static void DeleteRequestCB(int request_id, data_control_h provider, const char *where, void *user_data)
{
}

static void SelectRequestCB(int request_id, data_control_h provider, const char **column_list, int column_count, const char *where, const char *order, void *user_data)
{

}

static void UpdateRequestCB(int request_id, data_control_h provider, bundle *update_data, const char *where, void *user_data)
{

}

/***************************************************************************End CallBack Functions********************************************************/

/**
* @function 		ITs_data_control_provider_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_provider_startup(void)
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
	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
		{
			g_bDataControlCreation = true;
		}
	}
}

/**
* @function 		ITs_data_control_provider_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_provider_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_stSqlProvider);
		data_control_map_destroy(g_stMapProvider);
	}
}

/** @addtogroup itc-data-control-provider-testcases
*  @brief 		Integration testcases for module data-control-provider
*  @ingroup 	itc-data-control-provider
*  @{
*/

/**
* @testcase 			ITc_data_control_provider_data_control_provider_create_delete_statement_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_create_delete_statement
* @scenario				Call data_control_provider_create_delete_statement
* @apicovered			data_control_provider_create_delete_statement
* @passcase				When data_control_provider_create_delete_statement is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_create_delete_statement
//& type: auto
int ITc_data_control_provider_data_control_provider_create_delete_statement_p(void)
{
	START_TEST;

	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	// Target API
	char *pszQuery = data_control_provider_create_delete_statement(g_stSqlProvider, g_szWhere);
	CHECK_VALUE_STRING(pszQuery, "data_control_provider_create_delete_statement");

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_create_insert_statement_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_create_insert_statement
* @scenario				Call data_control_provider_create_insert_statement
* @apicovered			data_control_provider_create_insert_statement
* @passcase				When data_control_provider_create_insert_statement is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_create_insert_statement
//& type: auto
int ITc_data_control_provider_data_control_provider_create_insert_statement_p(void)
{
	START_TEST;

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);

	// Target API
	char *pszQuery = data_control_provider_create_insert_statement(g_stSqlProvider, pstData);
	bundle_free(pstData);
	CHECK_VALUE_STRING(pszQuery, "data_control_provider_create_insert_statement");
	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_create_update_statement_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_create_update_statement
* @scenario				Call data_control_provider_create_update_statement
* @apicovered			data_control_provider_create_update_statement
* @passcase				When data_control_provider_create_update_statement is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_create_update_statement
//& type: auto
int ITc_data_control_provider_data_control_provider_create_update_statement_p(void)
{
	START_TEST;

	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);

	// Target API
	char *pszQuery = data_control_provider_create_update_statement(g_stSqlProvider, pstData, g_szWhere);
	bundle_free(pstData);
	CHECK_VALUE_STRING(pszQuery, "data_control_provider_create_update_statement");

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_create_select_statement_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_create_select_statement
* @scenario				Call data_control_provider_create_select_statement
* @apicovered			data_control_provider_create_select_statement
* @passcase				When data_control_provider_create_select_statement is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_create_select_statement
//& type: auto
int ITc_data_control_provider_data_control_provider_create_select_statement_p(void)
{
	START_TEST;

	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	const char *pszColoumn = DUMMYKEY;
	const char *pszOrder = "WORD ASC";

	// Target API
	char *pszQuery = data_control_provider_create_select_statement(g_stSqlProvider, &pszColoumn, 1, g_szWhere, pszOrder);
	CHECK_VALUE_STRING(pszQuery, "data_control_provider_create_select_statement");

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_sql_register_unregister_cb_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_sql_register_cb and data_control_provider_sql_unregister_cb
* @scenario				Call data_control_provider_sql_register_cb\n
*						Call data_control_provider_sql_unregister_cb
* @apicovered			data_control_provider_sql_register_cb, data_control_provider_sql_unregister_cb
* @passcase				When data_control_provider_sql_register_cb and data_control_provider_sql_unregister_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_sql_register_cb and data_control_provider_sql_unregister_cb
//& type: auto
int ITc_data_control_provider_data_control_provider_sql_register_unregister_cb_p(void)
{
	START_TEST;

	data_control_provider_sql_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlProviderSqlInsertCb;
	stSqlCallBack.delete_cb = DataControlProviderSqlRemoveCb;

	// Target API
	int nRet = data_control_provider_sql_register_cb(&stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_sql_register_cb", DataControlGetError(nRet));

	// Target API
	nRet = data_control_provider_sql_unregister_cb();
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_sql_unregister_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_map_register_unregister_cb_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_map_register_cb and data_control_provider_map_unregister_cb
* @scenario				Call data_control_provider_map_register_cb\n
*						Call data_control_provider_map_unregister_cb
* @apicovered			data_control_provider_map_register_cb, data_control_provider_map_unregister_cb
* @passcase				When data_control_provider_map_register_cb and data_control_provider_map_unregister_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_map_register_cb and data_control_provider_map_unregister_cb
//& type: auto
int ITc_data_control_provider_data_control_provider_map_register_unregister_cb_p(void)
{
	START_TEST;

	data_control_provider_map_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlProviderMapInsertCb;
	stMapCallBack.remove_cb = DataControlProviderMapRemoveCb;

	// Target API
	int nRet = data_control_provider_map_register_cb(&stMapCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_map_register_cb", DataControlGetError(nRet));

	// Target API
	nRet = data_control_provider_map_unregister_cb();
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_map_unregister_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_match_data_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_match_data_id
* @scenario				Call data_control_provider_match_data_id
* @apicovered			data_control_provider_match_data_id
* @passcase				When data_control_provider_match_data_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_match_data_id
//& type: auto
int ITc_data_control_provider_data_control_provider_match_data_id_p(void)
{
	START_TEST;

	// Target API
	bool bResult = data_control_provider_match_data_id(g_stSqlProvider, SQLDATAID);
	if ( bResult == false )
	{
		FPRINTF("[Line : %d][%s] data_control_provider_match_data_id failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_data_control_provider_match_provider_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_provider_match_provider_id
* @scenario				Call data_control_provider_match_provider_id
* @apicovered			data_control_provider_match_provider_id
* @passcase				When data_control_provider_match_provider_id is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_match_provider_id
//& type: auto
int ITc_data_control_provider_data_control_provider_match_provider_id_p(void)
{
	START_TEST;

	// Target API
	bool bResult = data_control_provider_match_provider_id(g_stSqlProvider, SQLPROVIDERID);
	if ( bResult == false )
	{
		FPRINTF("[Line : %d][%s] data_control_provider_match_provider_id failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	return 0;
}

/**
* @testcase 			ITc_data_control_provider_add_remove_data_change_consumer_filter_cb_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Adds/Remove a consumer filter for the data changed callback addition process.
* @scenario				Call data_control_provider_add_data_change_consumer_filter_cb, data_control_provider_remove_data_change_consumer_filter_cb
* @apicovered			data_control_provider_add_data_change_consumer_filter_cb, data_control_provider_remove_data_change_consumer_filter_cb
* @passcase				When data_control_provider_add_data_change_consumer_filter_cb, data_control_provider_remove_data_change_consumer_filter_cb is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_add_data_change_consumer_filter_cb
//& type: auto
int ITc_data_control_provider_add_remove_data_change_consumer_filter_cb_p(void)
{
	START_TEST;
	
	int pCallbackId = -1;
		
	// Target API	
	int nRet = data_control_provider_add_data_change_consumer_filter_cb( DataControlProviderDataChangeConsumerFilterCB, NULL, &pCallbackId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_add_data_change_consumer_filter_cb", DataControlGetError(nRet));

	/*
	* Callback hit for DataControlProviderDataChangeConsumerFilterCB can't be checked as discussed with developer
	* Because to check callback hit, it needs consumer app. Not in TCT scope
	*/
	if( pCallbackId == -1)
	{
		FPRINTF("[Line : %d][%s] Get ID is incorrect\\n", __LINE__, API_NAMESPACE);	
		return 1;
	}
	
	nRet = data_control_provider_remove_data_change_consumer_filter_cb(pCallbackId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_remove_data_change_consumer_filter_cb", DataControlGetError(nRet));
		
	return 0;
}

/**
* @testcase 			ITc_data_control_provider_foreach_data_change_consumer_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Retrieves ids of all applications which receive data change notifications from a given provider.
* @scenario				Call data_control_provider_foreach_data_change_consumer data_control_provider_sql_unregister_cb
* @apicovered			data_control_provider_foreach_data_change_consumer data_control_provider_sql_unregister_cb
* @passcase				When data_control_provider_foreach_data_change_consumer data_control_provider_sql_unregister_cb is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_foreach_data_change_consumer
//& type: auto
int ITc_data_control_provider_foreach_data_change_consumer_p(void)
{
	int nRet = 0;
	data_control_h hProvider;
	
	nRet = data_control_sql_create(&hProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_create", DataControlGetError(nRet));
	CHECK_HANDLE(hProvider, "data_control_sql_create");
	
	
	nRet = data_control_sql_set_provider_id(hProvider, PROVIDER_ID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_provider_id", DataControlGetError(nRet),data_control_sql_destroy(hProvider));
	
	nRet = data_control_sql_set_data_id(hProvider, SQL_DATA_ID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_data_id", DataControlGetError(nRet),data_control_sql_destroy(hProvider));
	
	data_control_provider_sql_cb *sql_callback;
	sql_callback = (data_control_provider_sql_cb *) malloc(sizeof(data_control_provider_sql_cb));
	if( sql_callback == NULL)
	{
		FPRINTF("[Line : %d][%s] Memory Allocation of sql_callback failed\\n", __LINE__, API_NAMESPACE);
		data_control_sql_destroy(hProvider);
		return 1;

	}
	sql_callback->select_cb = SelectRequestCB;
	sql_callback->insert_cb = InsertRequestCB;
	sql_callback->delete_cb = DeleteRequestCB;
	sql_callback->update_cb = UpdateRequestCB;
	
	nRet = data_control_provider_sql_register_cb(sql_callback, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_sql_register_cb", DataControlGetError(nRet),data_control_sql_destroy(hProvider);FREE_MEMORY(sql_callback));
	
	nRet = data_control_provider_foreach_data_change_consumer(hProvider, &ChangeNotiConsumerListCB, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_foreach_data_change_consumer", DataControlGetError(nRet),data_control_sql_destroy(hProvider);FREE_MEMORY(sql_callback));
	/*
	* Callback hit for ChangeNotiConsumerListCB can't be checked as discussed with developer
	* Because to check callback hit, it needs consumer app. Not in TCT scope
	*/

	nRet = data_control_provider_sql_unregister_cb();
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_provider_sql_unregister_cb", DataControlGetError(nRet),FREE_MEMORY(sql_callback));
	
	FREE_MEMORY(sql_callback);
	
	nRet = data_control_sql_destroy(hProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_destroy", DataControlGetError(nRet));
	
	return 0;
}

/** @} */
/** @} */
