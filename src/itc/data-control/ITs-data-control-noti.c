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

static data_control_h g_DataControlProvider;
static char *pResultCBUserData = "user1";
static char *pNotuCBUserData = "user2";
static int pCallbackId;

/** @addtogroup itc-data-control
*  @ingroup itc
*  @{
*/

/**
* @function 		DataControlDataChangeCB
* @description	 	Called when received data changed notification from provider application.
* @parameter		data_control_h provider, data_control_data_change_type_e type, bundle *data, void *user_data
* @return 			NA
*/
static void DataControlDataChangeCB(data_control_h provider, data_control_data_change_type_e type,	bundle *data,	void *user_data)
{
	FPRINTF("[%s:%d] DataControlDataChangeCB hit\\n", __FUNCTION__, __LINE__);
	
	g_bAddCallbackResult = true;
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	normal_exit(0);	
}

static void InsertResponseCB(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data)
{
}

/**
* @function 		AddDataChangedCallbackResultCB
* @description	 	Called when received data changed notification from provider application.
* @parameter		data_control_h provider, data_control_error_e result, int callback_id, void *user_data
* @return 			NA
*/
static void AddDataChangedCallbackResultCB( data_control_h provider, data_control_error_e result, int callback_id, void *user_data)
{
	g_bDataChangeCallbackHit = true;
	int req_id;
	FPRINTF("[%s:%d] AddDataChangedCallbackResultCB hit\\n", __FUNCTION__, __LINE__);
	
	bundle *b = bundle_create();
	bundle_add_str(b, "WORD", "'test'");
	bundle_add_str(b, "WORD_DESC", "'test desc'");

	data_control_sql_insert(g_DataControlProvider, b, &req_id);
	bundle_free(b);	
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}	
}

/**
 * @function		ITs_data_control_noti_startup
 * @description		Called before each test
 * @parameter		NA
 * @return		NA
 */
void ITs_data_control_noti_startup(void)
{

	struct stat buf;
	if ( stat(ERR_LOG, &buf) == 0 )
	{
		remove(ERR_LOG);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	TCT_CheckInstalledApp(1, TEST_DATACONTROLNOT_APPID);
	g_bDataControlCreation = false;
	if ( DataControlNotiSqlHandle(&g_DataControlProvider) == true )
	{		
		g_bDataControlCreation = true;	
	}
}

/**
 * @function		ITs_data_control_noti_cleanup
 * @description		Called after each test
 * @parameter		NA
 * @return		NA
 */
void ITs_data_control_noti_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif

	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_DataControlProvider);		
	}
}

/**
* @testcase 			ITs_data_control_add_remove_data_change_cb_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Sends a data change notification to consumer applications which have successfully added a data change callback.
* @scenario				Call data_control_add_data_change_cb data_control_provider_send_data_change_noti
* @apicovered			data_control_add_data_change_cb data_control_provider_send_data_change_noti
* @passcase				When data_control_add_data_change_cb data_control_provider_send_data_change_noti is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_add_data_change_cb data_control_provider_send_data_change_noti
//& type: auto
int ITs_data_control_add_remove_data_change_cb_p(void)
{
	START_TEST;
	int result;
	data_control_sql_response_cb sql_callback;
	sql_callback.insert_cb = InsertResponseCB;
	int nTimeoutId = 0 ;	
	g_bAddCallbackResult = false;
	g_bDataChangeCallbackHit = false;
	
	result = data_control_sql_register_response_cb(g_DataControlProvider, &sql_callback, NULL);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, result, "data_control_sql_register_response_cb", DataControlGetError(result));
	
	//Target API
	result = data_control_add_data_change_cb(g_DataControlProvider,
				DataControlDataChangeCB,
				pNotuCBUserData,
				AddDataChangedCallbackResultCB,
				pResultCBUserData,
				&pCallbackId);

	g_bCallbackHit = false;

	RUN_POLLING_LOOP;	
			
	if ( g_bDataChangeCallbackHit == false )
	{
		FPRINTF("[Line : %d][%s] callback AddDataChangedCallbackResultCB not invoked\\n", __LINE__, API_NAMESPACE);
		data_control_remove_data_change_cb(g_DataControlProvider, pCallbackId);
		return 1;
	}
	
	nTimeoutId = 0 ;
	RUN_POLLING_LOOP;
	
	if ( g_bAddCallbackResult == false )
	{	
		FPRINTF("[Line : %d][%s] callback DataControlDataChangeCB not invoked\\n", __LINE__, API_NAMESPACE);
		data_control_remove_data_change_cb(g_DataControlProvider, pCallbackId);
		return 1;
	}	
	
	//Target API
	result = data_control_remove_data_change_cb(g_DataControlProvider, pCallbackId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, result, "data_control_remove_data_change_cb", DataControlGetError(result));
		
	return 0;
}

/**
* @testcase 			ITc_data_control_sql_register_response_cb_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			register  sql response callback
* @scenario				Call data_control_sql_register_response_cb
* @apicovered			data_control_sql_register_response_cb
* @passcase				When data_control_sql_register_response_cb is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_register_response_cb
//& type: auto
int ITc_data_control_sql_register_response_cb_p(void)
{
	START_TEST;

	data_control_sql_response_cb sql_callback;
	sql_callback.insert_cb = InsertResponseCB;

	int result = data_control_sql_register_response_cb(g_DataControlProvider, &sql_callback, NULL);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, result, "data_control_sql_register_response_cb", DataControlGetError(result));
	
	return 0;
}
/**
* @testcase 			ITc_data_control_provider_send_data_change_noti_p
* @since_tizen 			3.0
* @author				SRID(gaurav.m2)
* @reviewer				SRID(a.pandia1)
* @type 				auto
* @description			Sends a data change notification to consumer applications which have successfully added a data change callback.
* @scenario				Call data_control_provider_send_data_change_noti
* @apicovered			data_control_provider_send_data_change_noti
* @passcase				When data_control_provider_send_data_change_noti is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Sends a data change notification to consumer applications which have successfully added a data change callback.
//& type: auto
int ITc_data_control_provider_send_data_change_noti_p(void)
{
	START_TEST;
	
	int nTimeoutId = 0;

	bundle *pBundleData = bundle_create();
	if ( pBundleData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	
	int result = data_control_provider_send_data_change_noti(g_DataControlProvider, DATA_CONTROL_DATA_CHANGE_SQL_INSERT, pBundleData);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, result, "data_control_provider_send_data_change_noti", DataControlGetError(result),bundle_free(pBundleData));
	
	bundle_free(pBundleData);
	
	return 0;
}

/** @} */
/** @} */
