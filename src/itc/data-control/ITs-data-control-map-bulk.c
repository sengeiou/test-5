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
* @function 		DataControlMapGetCb
* @description	 	Called when record is retrieved
* @parameter		int request_id, data_control_h provider, char ** result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapGetCb(int request_id, data_control_h provider, char **result_value_list, int result_value_count, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlMapGetCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	int nGetHandleID;

	int nRet = data_control_map_get_handle_id(provider, &nGetHandleID);
	if (nRet != DATA_CONTROL_ERROR_NONE)
	{
		normal_exit(1);
	}

	if (nGetHandleID == g_nProviderHandleId)
	{
		g_bCheckHandleId = true;
	}

	if (nGetHandleID == g_nProviderHandleIdForBind)
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
* @function 		DataControlMapAddCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapAddCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlMapAddCb Callback invoked\\n", __LINE__, API_NAMESPACE);
	int nGetHandleID;
	int nRet = data_control_map_get_handle_id(provider, &nGetHandleID);

	if (nRet != DATA_CONTROL_ERROR_NONE)
	{
		normal_exit(1);
	}

	if (nGetHandleID == g_nProviderHandleId)
	{
		g_bCheckHandleId = true;
	}

	if (nGetHandleID == g_nProviderHandleIdForBind)
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
* @function 		DataControlMapRemoveCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapRemoveCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlMapRemoveCb Callback invoked\\n", __LINE__, API_NAMESPACE);
}

/**
* @function 		DataControlMapSetCb
* @description	 	Called when record is changed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlMapSetCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlMapSetCb Callback invoked\\n", __LINE__, API_NAMESPACE);
}

static void DataControlMapBulkAddCb(int request_id, data_control_h provider, data_control_bulk_result_data_h bulk_results, bool provider_result, const char *error, void *user_data)
{
	FPRINTF("[Line : %d][%s] DataControlMapBulkAddCb Callback invoked\\n", __LINE__, API_NAMESPACE);

	int nGetHandleID;
	int nRet = data_control_map_get_handle_id(provider, &nGetHandleID);

	if (nRet != DATA_CONTROL_ERROR_NONE)
	{
		normal_exit(1);
	}

	if (nGetHandleID == g_nProviderHandleId)
	{
		g_bCheckHandleId = true;
	}

	if (nGetHandleID == g_nProviderHandleIdForBind)
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

/***************************************************************************End CallBack Functions********************************************************/

/**
* @function 		ITs_data_control_map_bulk_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_map_bulk_startup(void)
{
	struct stat buf;
	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;
	g_nProviderHandleId = -1;
	g_nProviderHandleIdForBind = -1;
	g_stMapProvider = NULL;
	g_stMapProviderForBind = NULL;
	g_bDataControlCreation = false;

	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_DATACONTROL_APPID);

	if ( DataControlInitiateMapBulkHandle(&g_stMapProvider) == false )
	{
		return;
	}

	int nRet = data_control_map_get_handle_id(g_stMapProvider, &g_nProviderHandleId);
	if(nRet != DATA_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] data_control_map_get_handle_id, error = %s\\n", __LINE__, API_NAMESPACE,  DataControlGetError(nRet));
		return;
	}

	if ( DataControlInitiateMapBulkHandle(&g_stMapProviderForBind) == false )
	{
		return;
	}

	nRet = data_control_map_get_handle_id(g_stMapProviderForBind, &g_nProviderHandleIdForBind);
	if(nRet != DATA_CONTROL_ERROR_NONE)
	{
		FPRINTF("[Line : %d][%s] data_control_map_get_handle_id, error = %s\\n", __LINE__, API_NAMESPACE,  DataControlGetError(nRet));
		return;
	}

	g_bDataControlCreation = true;
}

/**
* @function 		ITs_data_control_map_bulk_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_map_bulk_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_stMapProvider != NULL )
	{
		data_control_map_destroy(g_stMapProvider);
		g_stMapProvider = NULL;
	}

	if ( g_stMapProviderForBind != NULL )
	{
		data_control_map_destroy(g_stMapProviderForBind);
		g_stMapProviderForBind = NULL;
	}
}

//& purpose: Binds and unbinds a response callback function to a data control provider handle
//& type: auto
/**
* @testcase 			ITc_data_control_map_bind_unbind_response_cb_p
* @since_tizen 			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Binds and unbinds a response callback function to a data control provider handle
* @scenario				Binds and unbinds a response callback function to a data control provider handle
* @apicovered			data_control_map_bind_response_cb, data_control_map_unbind_response_cb
* @passcase				When data_control_map_bind_response_cb and data_control_map_unbind_response_cb is successful
* @failcase				If target APIs fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_map_bind_unbind_response_cb_p(void)
{
	START_TEST;

	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;
	data_control_map_response_cb map_callback = {0};
	map_callback.get_cb = DataControlMapGetCb;
	map_callback.add_cb = DataControlMapAddCb;
	map_callback.remove_cb = DataControlMapRemoveCb;
	map_callback.set_cb = DataControlMapSetCb;

	int nRet = data_control_map_bind_response_cb(g_stMapProvider, &map_callback, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_bind_response_cb", DataControlGetError(nRet), data_control_map_unbind_response_cb(g_stMapProvider));

	nRet = data_control_map_bind_response_cb(g_stMapProviderForBind, &map_callback, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_bind_response_cb", DataControlGetError(nRet), data_control_map_unbind_response_cb(g_stMapProvider);data_control_map_unbind_response_cb(g_stMapProviderForBind));

	const char *pszKey = DUMMYKEY;
	int nRequestId;

	nRet = data_control_map_get(g_stMapProvider, pszKey, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unbind_response_cb(g_stMapProvider);data_control_map_unbind_response_cb(g_stMapProviderForBind));
	RUN_POLLING_LOOP;

	nRet = data_control_map_get(g_stMapProviderForBind, pszKey, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_unbind_response_cb(g_stMapProvider);data_control_map_unbind_response_cb(g_stMapProviderForBind));
	RUN_POLLING_LOOP;

	if (!g_bCheckHandleId || !g_bCheckHandleIdForBind)
	{
		data_control_map_unbind_response_cb(g_stMapProvider);
		data_control_map_unbind_response_cb(g_stMapProviderForBind);
		return 1;
	}

	nRet = data_control_map_unbind_response_cb(g_stMapProviderForBind);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unbind_response_cb", DataControlGetError(nRet), data_control_map_unbind_response_cb(g_stMapProvider));

	nRet = data_control_map_unbind_response_cb(g_stMapProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unbind_response_cb", DataControlGetError(nRet));
	normal_exit(0);

	return 0;
}

//& purpose: Binds and unbinds the add bulk data callback to the map data control response
//& type: auto
/**
* @testcase 			ITc_data_control_map_bind_unbind_add_bulk_data_response_cb_p
* @since_tizen 			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Binds and unbinds the add bulk data callback to the map data control response
* @scenario				Binds and unbinds the add bulk data callback to the map data control response
* @apicovered			data_control_map_bind_add_bulk_data_response_cb, data_control_map_unbind_add_bulk_data_response_cb
* @passcase				When data_control_map_bind_add_bulk_data_response_cb and data_control_map_unbind_add_bulk_data_response_cb is successful
* @failcase				If target APIs fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_map_bind_unbind_add_bulk_data_response_cb_p(void)
{
	START_TEST;
	g_bCheckHandleId = false;
	g_bCheckHandleIdForBind = false;

	int nRet = data_control_map_bind_add_bulk_data_response_cb(g_stMapProvider, DataControlMapBulkAddCb, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_bind_add_bulk_data_response_cb", DataControlGetError(nRet), data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider));

	nRet = data_control_map_bind_add_bulk_data_response_cb(g_stMapProviderForBind, DataControlMapBulkAddCb, NULL);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_bind_add_bulk_data_response_cb", DataControlGetError(nRet), data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));

	data_control_bulk_data_h bulk_data_h;

	nRet = data_control_bulk_data_create(&bulk_data_h);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_bulk_data_create", DataControlGetError(nRet), data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));

	CHECK_HANDLE_CLEANUP(bulk_data_h, "bundle_create", data_control_bulk_data_destroy(bulk_data_h);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));
	
	bundle *b1 = bundle_create();
	CHECK_HANDLE_CLEANUP(b1, "bundle_create", data_control_bulk_data_destroy(bulk_data_h);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));
	bundle_add_str(b1, "key", "test key");
	bundle_add_str(b1, "value", "test value");

	bundle *b2 = bundle_create();
	CHECK_HANDLE_CLEANUP(b2, "bundle_create", bundle_free(b1); data_control_bulk_data_destroy(bulk_data_h);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));
	bundle_add_str(b2, "key", "test key2");
	bundle_add_str(b2, "value", "test value2");

	data_control_bulk_data_create(&bulk_data_h);
	data_control_bulk_data_add(bulk_data_h, b1);
	data_control_bulk_data_add(bulk_data_h, b2);

	int nRequestId;
	nRet = data_control_map_add_bulk_data(g_stMapProviderForBind, bulk_data_h, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add_bulk_data", DataControlGetError(nRet),  bundle_free(b1); bundle_free(b2); data_control_bulk_data_destroy(bulk_data_h);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));
	RUN_POLLING_LOOP;

	nRet = data_control_map_add_bulk_data(g_stMapProvider, bulk_data_h, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_add_bulk_data", DataControlGetError(nRet),  bundle_free(b1); bundle_free(b2); data_control_bulk_data_destroy(bulk_data_h); data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider); data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));
	RUN_POLLING_LOOP;

	bundle_free(b1);
	bundle_free(b2);

	if (!g_bCheckHandleId || !g_bCheckHandleIdForBind)
	{
		data_control_bulk_data_destroy(bulk_data_h);
		data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);
		data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind);
		return 1;
	}

	nRet = data_control_bulk_data_destroy(bulk_data_h);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_bulk_data_destroy", DataControlGetError(nRet));

	nRet = data_control_map_unbind_add_bulk_data_response_cb(g_stMapProvider);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unbind_add_bulk_data_response_cb", DataControlGetError(nRet), data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind));

	data_control_map_unbind_add_bulk_data_response_cb(g_stMapProviderForBind);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_unbind_add_bulk_data_response_cb", DataControlGetError(nRet));

	return 0;
}

//& purpose: Gets the handle ID for a provider
//& type: auto
/**
* @testcase 			ITc_data_control_map_get_handle_id_p
* @since_tizen 			4.0
* @author				SRID(manmohan.k)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Gets the handle ID for a provider
* @scenario				Gets the handle ID for a provider
* @apicovered			data_control_map_get_handle_id
* @passcase				When data_control_map_get_handle_id is successful
* @failcase				If data_control_map_get_handle_id fails
* @precondition			None
* @postcondition		None
*/
int ITc_data_control_map_get_handle_id_p(void)
{
	START_TEST;
	int handleId;
	int nRet = data_control_map_get_handle_id(g_stMapProvider, &handleId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_handle_id", DataControlGetError(nRet));
	normal_exit(0);

	return 0;
}
/** @} */
/** @} */