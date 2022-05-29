//
// Copyright (c) 2014 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//	   http://www.apache.org/licenses/LICENSE-2.0
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
* @function			DataControlSqlInsertCb
* @description		Called when record is inserted
* @parameter		int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data
* @return			NA
*/
static void DataControlSqlInsertCb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlSqlInsertCb callback Invoked\\n", __LINE__, API_NAMESPACE);

	int nHandleId;

	int nRet = data_control_sql_get_handle_id(provider, &nHandleId);
	if (nRet != DATA_CONTROL_ERROR_NONE)
	{
		normal_exit(1);
	}

	if (nHandleId == g_nProviderHandleId)
	{
		g_bCheckHandleId = true;
	}

	if (nHandleId == g_nProviderHandleIdForBind)
	{
		g_bCheckHandleIdForBind = true;
	}

	if (g_bCheckHandleId && g_bCheckHandleIdForBind)
	{
		normal_exit(0);
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
}


/**
* @function			DataControlSqlSelectCb
* @description		Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return			NA
*/
static void DataControlSqlSelectCb(int request_id, data_control_h provider, result_set_cursor cursor, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlSqlSelectCb callback Invoked\\n", __LINE__, API_NAMESPACE);
}


/**
* @function			DataControlSqlUpdateCb
* @description		Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return			NA
*/
static void DataControlSqlUpdateCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlSqlUpdateCb callback Invoked\\n", __LINE__, API_NAMESPACE);
}


/**
* @function			DataControlSqlRemoveCb
* @description		Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return			NA
*/
static void DataControlSqlRemoveCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlSqlRemoveCb callback Invoked\\n", __LINE__, API_NAMESPACE);
}

static void DataControlSqlBulkInsertCb(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlSqlBulkInsertCb callback Invoked\\n", __LINE__, API_NAMESPACE);

	 int nHandleId;

	int nRet = data_control_sql_get_handle_id(provider, &nHandleId);
	if (nRet != DATA_CONTROL_ERROR_NONE)
	{
		normal_exit(1);
	}

	if (nHandleId == g_nProviderHandleId)
	{
		g_bCheckHandleId = true;
	}

	if (nHandleId == g_nProviderHandleIdForBind)
	{
		g_bCheckHandleIdForBind = true;
	}

	if (g_bCheckHandleId && !g_bCheckHandleIdForBind)
	{
		normal_exit(0);
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
}

/***************************************************************************End CallBack Functions********************************************************/

/**
* @function			ITs_data_control_sql_bulk_startup
* @description		Called before each test, set the service boolean true
* @parameter		NA
* @return			NA
*/
void ITs_data_control_sql_bulk_startup(void)
{
	struct stat buf;
	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;
	g_nProviderHandleId = -1;
	g_nProviderHandleIdForBind = -1;
	g_bDataControlCreation = false;
	g_stSqlProvider = NULL;
	g_stSqlProviderForBind = NULL;

	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_DATACONTROL_APPID);

	if ( DataControlInitiateSqlBulkHandle(&g_stSqlProvider) == false )
	{
		return;
	}

	int nRet = data_control_sql_get_handle_id(g_stSqlProvider, &g_nProviderHandleId);
	if(nRet != DATA_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] data_control_sql_get_handle_id, error = %s\\n", __LINE__, API_NAMESPACE,  DataControlGetError(nRet));
		return;
	}

	if ( DataControlInitiateSqlBulkHandle(&g_stSqlProviderForBind) == false )
	{
		return;
	}

	nRet = data_control_sql_get_handle_id(g_stSqlProviderForBind, &g_nProviderHandleIdForBind);
	if(nRet != DATA_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] data_control_sql_get_handle_id, error = %s\\n", __LINE__, API_NAMESPACE,  DataControlGetError(nRet));
		return;
	}

	g_bDataControlCreation = true;
}

/**
* @function			ITs_data_control_sql_bulk_cleanup
* @description		Called after each test
* @parameter		NA
* @return			NA
*/
void ITs_data_control_sql_bulk_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_stSqlProvider != NULL )
	{
		data_control_sql_destroy(g_stSqlProvider);
		g_stSqlProvider = NULL;
	}

	if ( g_stSqlProviderForBind != NULL )
	{
		data_control_sql_destroy(g_stSqlProviderForBind);
		g_stSqlProviderForBind = NULL;
	}
}

//& purpose: Binds and unbinds a callback function to the SQL data control response
//& type: auto
/**
* @testcase				ITc_data_control_sql_bind_unbind_response_cb_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Binds and unbinds a callback function to the SQL data control response
* @scenario				Binds and unbinds a callback function to the SQL data control response
* @apicovered			data_control_sql_bind_response_cb, data_control_sql_unbind_response_cb
* @passcase				When data_control_sql_bind_response_cb and data_control_sql_unbind_response_cb is successful
* @failcase				If target APIs fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_sql_bind_unbind_response_cb_p(void)
{
	START_TEST;

	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;

	data_control_sql_response_cb sql_callback;
	sql_callback.insert_cb = DataControlSqlInsertCb;
	sql_callback.select_cb = DataControlSqlSelectCb;
	sql_callback.update_cb = DataControlSqlUpdateCb;
	sql_callback.delete_cb = DataControlSqlRemoveCb;

	int nRet = data_control_sql_bind_response_cb(g_stSqlProvider, &sql_callback, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_bind_response_cb", DataControlGetError(nRet), data_control_sql_unbind_response_cb(g_stSqlProvider));

	nRet = data_control_sql_bind_response_cb(g_stSqlProviderForBind, &sql_callback, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_bind_response_cb", DataControlGetError(nRet), data_control_sql_unbind_response_cb(g_stSqlProvider); data_control_sql_unbind_response_cb(g_stSqlProviderForBind));

	bundle *b = bundle_create();
	CHECK_HANDLE_CLEANUP(b, "bundle_create", data_control_sql_unbind_response_cb(g_stSqlProvider); data_control_sql_unbind_response_cb(g_stSqlProviderForBind));
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test description'");
	bundle_add_str(b, "WORD_NUM", "1");

	int nRequestId = 0;
	nRet = data_control_sql_insert(g_stSqlProvider, b, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(b); data_control_sql_unbind_response_cb(g_stSqlProvider); data_control_sql_unbind_response_cb(g_stSqlProviderForBind));
	RUN_POLLING_LOOP;

	nRet = data_control_sql_insert(g_stSqlProviderForBind, b, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(b); data_control_sql_unbind_response_cb(g_stSqlProvider); data_control_sql_unbind_response_cb(g_stSqlProviderForBind));
	RUN_POLLING_LOOP;

	bundle_free(b);

	if (!g_bCheckHandleId || !g_bCheckHandleIdForBind)
	{
		data_control_sql_unbind_response_cb(g_stSqlProviderForBind);
		data_control_sql_unbind_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unbind_response_cb(g_stSqlProviderForBind);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unbind_response_cb", DataControlGetError(nRet), data_control_sql_unbind_response_cb(g_stSqlProvider));

	nRet = data_control_sql_unbind_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unbind_response_cb", DataControlGetError(nRet));
	normal_exit(0);

	return 0;
}

//& purpose: Binds and Unbinds he insert bulk data callback to the SQL data control response
//& type: auto
/**
* @testcase				ITc_data_control_sql_bind_unbind_insert_bulk_data_response_cb_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Binds and Unbinds he insert bulk data callback to the SQL data control response
* @scenario				Binds and Unbinds he insert bulk data callback to the SQL data control response\n
* @apicovered			data_control_sql_bind_insert_bulk_data_response_cb, data_control_sql_unbind_insert_bulk_data_response_cb
* @passcase				When data_control_sql_bind_insert_bulk_data_response_cb and data_control_sql_unbind_insert_bulk_data_response_cb is successful
* @failcase				If target APIs fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_sql_bind_unbind_insert_bulk_data_response_cb_p(void)
{
	START_TEST;
	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;

	int nRet = data_control_sql_bind_insert_bulk_data_response_cb(g_stSqlProvider, DataControlSqlBulkInsertCb, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_bind_insert_bulk_data_response_cb", DataControlGetError(nRet), data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider));

	nRet = data_control_sql_bind_insert_bulk_data_response_cb(g_stSqlProviderForBind, DataControlSqlBulkInsertCb, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_bind_insert_bulk_data_response_cb", DataControlGetError(nRet), data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));


	bundle *b1 = bundle_create();
	CHECK_HANDLE_CLEANUP(b1, "bundle_create", data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	bundle *b2 = bundle_create();
	CHECK_HANDLE_CLEANUP(b1, "bundle_create", bundle_free(b1); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));
	bundle_add_str(b2, "WORD", "'test2'");
	bundle_add_str(b2, "WORD_DESC", "'test2 description'");

	data_control_bulk_data_h bulk_data_h;
	nRet = data_control_bulk_data_create(&bulk_data_h);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_bulk_data_create", DataControlGetError(nRet), bundle_free(b1); bundle_free(b2); data_control_bulk_data_destroy(bulk_data_h); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));

	data_control_bulk_data_add(bulk_data_h, b1);
	data_control_bulk_data_add(bulk_data_h, b2);

	int nRequestId;
	nRet = data_control_sql_insert_bulk_data(g_stSqlProvider, bulk_data_h, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert_bulk_data", DataControlGetError(nRet),	 bundle_free(b1); bundle_free(b2); data_control_bulk_data_destroy(bulk_data_h); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));
	RUN_POLLING_LOOP;

	nRet = data_control_sql_insert_bulk_data(g_stSqlProviderForBind, bulk_data_h, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert_bulk_data", DataControlGetError(nRet),	 bundle_free(b1); bundle_free(b2); data_control_bulk_data_destroy(bulk_data_h); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider); data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));
	RUN_POLLING_LOOP;

	bundle_free(b1);
	bundle_free(b2);

	if (!g_bCheckHandleId || !g_bCheckHandleIdForBind)
	{
		data_control_bulk_data_destroy(bulk_data_h);
		data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider);
		data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind);
		return 1;
	}

	nRet = data_control_bulk_data_destroy(bulk_data_h);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_bulk_data_destroy", DataControlGetError(nRet));


	nRet = data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProvider);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unbind_insert_bulk_data_response_cb", DataControlGetError(nRet), data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind));

	nRet = data_control_sql_unbind_insert_bulk_data_response_cb(g_stSqlProviderForBind);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unbind_insert_bulk_data_response_cb", DataControlGetError(nRet));

	return 0;
}

//& purpose: Gets the handle ID for a sql provider
//& type: auto
/**
* @testcase				ITc_data_control_sql_get_handle_id_p
* @since_tizen			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type					auto
* @description			Gets the handle ID for a sql provider
* @scenario				Gets the handle ID for a sql provider\n
* @apicovered			data_control_sql_get_handle_id
* @passcase				When data_control_sql_get_handle_id is successful
* @failcase				If data_control_sql_get_handle_id fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_sql_get_handle_id_p(void)
{
	START_TEST;

	int handleId;
	int nRet = data_control_sql_get_handle_id(g_stSqlProvider, &handleId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_get_handle_id", DataControlGetError(nRet));

	normal_exit(0);
	return 0;
}
/** @} */
/** @} */