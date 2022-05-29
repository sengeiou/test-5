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
* @function 		DataControlSqlInsertResponseCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlInsertResponseCb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data) 
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlInsertResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Insert operation successful at row %lld\\n", __LINE__, API_NAMESPACE, inserted_row_id);
		g_nRowId = inserted_row_id;
		g_bCallbackHit = true;
		if (g_bIsInsertDataCheck)
		{
			int result = 0;
			char* pszValue = "WORD";
			const char *pWhere = "WORD = 'TestValue'";
			
			result = data_control_sql_select(g_stSqlProvider, &pszValue, 1, pWhere, "WORD ASC", &request_id);
			if (result != DATA_CONTROL_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] Select operation failed inside Insert operation callback\\n", __LINE__, API_NAMESPACE);
			}
			return;
		}
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
* @function 		DataControlSqlRemoveResponseCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlRemoveResponseCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlRemoveResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Delete operation successful\\n", __LINE__, API_NAMESPACE);
		g_nRowId--;
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
* @function 		DataControlSqlUpdateResponseCb
* @description	 	Called when record is removed
* @parameter		int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlUpdateResponseCb(int request_id, data_control_h provider, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlUpdateResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Update operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
		if (g_bIsInsertDataCheck)
		{
			int result = 0;
			char* pszValue = "WORD";
			const char *pWhere = "WORD = 'TestValueNew'";
			result = data_control_sql_select(g_stSqlProvider, &pszValue, 1, pWhere, "WORD ASC", &request_id);
			if (result != DATA_CONTROL_ERROR_NONE)
			{
				FPRINTF("[Line : %d][%s] Select operation failed inside Update operation callback\\n", __LINE__, API_NAMESPACE);
			}
			return;
		}
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Update operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
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
* @function 		DataControlSqlSelectResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectResponseCb(int request_id, data_control_h provider, result_set_cursor cursor, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		g_bCallbackHit = true;
		if (g_bIsInsertDataCheck)
		{
			while (data_control_sql_step_next(cursor) == DATA_CONTROL_ERROR_NONE) 
			{
				data_control_sql_get_text_data(cursor, 0, g_szWordDesc);
			}
		}
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
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
* @function 		DataControlSqlSelectBlobResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectBlobResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectBlobResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		void *pData = (void *) malloc(TESTSTRINGSIZE);

		// Target API
		int nRet = data_control_sql_get_blob_data(enumerator, BLOBCOLOUMN, pData, TESTSTRINGSIZE);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_blob_data failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}

		FREE_MEMORY(pData);
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectIntResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectIntResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectIntResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		int nData = 0;

		// Target API
		int nRet = data_control_sql_get_int_data(enumerator, INTEGERCOLOUMN, &nData);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_int_data failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectInt64ResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectInt64ResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectInt64ResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		long long int nData = 0;

		// Target API
		int nRet = data_control_sql_get_int64_data(enumerator, INTEGERCOLOUMN, &nData);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_int64_data failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
		
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectTextResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectTextResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectTextResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		char szData[TESTVALUE] = {0};

		// Target API
		int nRet = data_control_sql_get_text_data(enumerator, STRINGCOLOUMN, szData);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_text_data failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
		
		
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectDoubleResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectDoubleResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectDoubleResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		double nData = 0;

		// Target API
		int nRet = data_control_sql_get_double_data(enumerator, DOUBLECOLOUMN, &nData);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_double_data failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnCountResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnCountResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnCountResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		// Target API
		int nRet = data_control_sql_get_column_count(enumerator);
		if ( nRet < 0 )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_column_count failed\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnSizeResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnSizeResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnSizeResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		// Target API
		int nRet = data_control_sql_get_column_item_size(enumerator, INTEGERCOLOUMN);
		if ( nRet < 0 )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_column_item_size failed\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnTypeResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnTypeResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnTypeResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		data_control_sql_column_type_e eType = DATA_CONTROL_SQL_COLUMN_TYPE_UNDEFINED;

		// Target API
		int nRet = data_control_sql_get_column_item_type(enumerator, INTEGERCOLOUMN, &eType);
		if ( (nRet != DATA_CONTROL_ERROR_NONE) || (eType == DATA_CONTROL_SQL_COLUMN_TYPE_UNDEFINED) )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_column_item_type failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnNameResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnNameResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnNameResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		char szData[TESTVALUE] = {0};

		// Target API
		int nRet = data_control_sql_get_column_name(enumerator, STRINGCOLOUMN, szData);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_column_name failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		else
		{
			g_bCallbackHit = true;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
		
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnStepFirstLastResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnStepFirstLastResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnStepFirstLastResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);

		g_bCallbackHit = true;

		// Target API
		int nRet = data_control_sql_step_first(enumerator);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_step_first failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}

		// Target API
		nRet = data_control_sql_step_last(enumerator);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_step_last failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
		g_bCallbackHit = false;
	}

	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}

/**
* @function 		DataControlSqlSelectColoumnStepNextPreviousResponseCb
* @description	 	Called when record is selected
* @parameter		int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static void DataControlSqlSelectColoumnStepNextPreviousResponseCb(int request_id, data_control_h provider, result_set_cursor enumerator, bool provider_result, const char *error, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlSelectColoumnStepNextPreviousResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	if ( provider_result )
	{
		FPRINTF("[Line : %d][%s] Select operation successful\\n", __LINE__, API_NAMESPACE);
		data_control_sql_step_first(enumerator);

		g_bCallbackHit = true;

		// Target API
		int nRet = data_control_sql_step_next(enumerator);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_step_next failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}

		// Target API
		nRet = data_control_sql_step_previous(enumerator);
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			FPRINTF("[Line : %d][%s] data_control_sql_step_previous failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
			g_bCallbackHit = false;
		}
		
		if(strcmp((char*)user_data,TESTSTRING) != 0)
		{
			FPRINTF("[Line : %d][%s] User data passed to callback does not match\\n", __LINE__, API_NAMESPACE);
			g_bCallbackHit = false;
		}
	}
	else 
	{
		FPRINTF("[Line : %d][%s] Select operation for request %d failed, error returned = %s\\n", __LINE__, API_NAMESPACE, request_id, error);
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
* @function 		ITs_data_control_sql_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_sql_startup(void)
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
	g_bIsInsertDataCheck = false;
	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		g_bDataControlCreation = true;
	}
}

/**
* @function 		ITs_data_control_sql_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_data_control_sql_cleanup(void)
{
	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_stSqlProvider);
	}

#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Data_Control_p\\n", __LINE__, API_NAMESPACE);
#endif
}

/** @addtogroup itc-data-control-sql-testcases
*  @brief 		Integration testcases for module data-control-sql
*  @ingroup 	itc-data-control-sql
*  @{
*/

/**
* @testcase 			ITc_data_control_sql_data_control_sql_destroy_create_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_destroy and data_control_sql_create
* @scenario				Call data_control_sql_destroy\n
*						Call data_control_sql_create
* @apicovered			data_control_sql_destroy, data_control_sql_create
* @passcase				When data_control_sql_destroy and data_control_sql_create are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_destroy and data_control_sql_create
//& type: auto
int ITc_data_control_sql_data_control_sql_destroy_create_p(void)
{
	START_TEST;

	// Target API
	int nRet = data_control_sql_destroy(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_destroy", DataControlGetError(nRet));
	g_bDataControlCreation = false;

	// Target API
	nRet = data_control_sql_create(&g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_create", DataControlGetError(nRet));
	if(g_stSqlProvider == NULL)
	{
		FPRINTF("[Line : %d][%s] data_control_sql_create failed, error = Handle returned is NULL\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	g_bDataControlCreation = true;
	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_set_get_data_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_set_data_id and data_control_sql_get_data_id
* @scenario				Call data_control_sql_set_data_id\n
*						Call data_control_sql_get_data_id
* @apicovered			data_control_sql_set_data_id, data_control_sql_get_data_id
* @passcase				When data_control_sql_set_data_id and data_control_sql_get_data_id are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_set_data_id and data_control_sql_get_data_id
//& type: auto
int ITc_data_control_sql_data_control_sql_set_get_data_id_p(void)
{
	START_TEST;

	char *pszDataId = NULL;

	// Target API
	int nRet = data_control_sql_set_data_id(g_stSqlProvider, SQLDATAID);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_data_id", DataControlGetError(nRet));

	// Target API
	nRet = data_control_sql_get_data_id(g_stSqlProvider, &pszDataId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_get_data_id", DataControlGetError(nRet));

	if ( strstr(pszDataId, SQLDATAID) == NULL )
	{
		FPRINTF("[Line : %d][%s] data_control_sql_get_data_id failed, as Data Id not found\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDataId);
		return 1;
	}
	FREE_MEMORY(pszDataId);
	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_set_get_provider_id_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_set_provider_id and data_control_sql_get_provider_id
* @scenario				Call data_control_sql_set_provider_id\n
*						Call data_control_sql_get_provider_id
* @apicovered			data_control_sql_set_provider_id, data_control_sql_get_provider_id
* @passcase				When data_control_sql_set_provider_id and data_control_sql_get_provider_id are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_set_provider_id and data_control_sql_get_provider_id
//& type: auto
int ITc_data_control_sql_data_control_sql_set_get_provider_id_p(void)
{
	START_TEST;

	char *pszDataId = NULL;

	// Target API
	int nRet = data_control_sql_set_provider_id(g_stSqlProvider, SQLPROVIDERID);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_provider_id", DataControlGetError(nRet));

	// Target API
	nRet = data_control_sql_get_provider_id(g_stSqlProvider, &pszDataId);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_get_provider_id", DataControlGetError(nRet));

	if ( strstr(pszDataId, SQLPROVIDERID) == NULL )
	{
		FPRINTF("[Line : %d][%s] data_control_sql_get_provider_id failed, as Data Id not found\\n", __LINE__, API_NAMESPACE);
		FREE_MEMORY(pszDataId);
		return 1;
	}
	FREE_MEMORY(pszDataId);
	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_register_unregister_response_cb_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_register_response_cb and data_control_sql_unregister_response_cb
* @scenario				Call data_control_sql_register_response_cb\n
*						Call data_control_sql_unregister_response_cb
* @apicovered			data_control_sql_register_response_cb, data_control_sql_unregister_response_cb
* @passcase				When data_control_sql_register_response_cb and data_control_sql_unregister_response_cb are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_register_response_cb and data_control_sql_unregister_response_cb
//& type: auto
int ITc_data_control_sql_data_control_sql_register_unregister_response_cb_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;

	// Target API
	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTSTRING);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet), bundle_free(pstData));

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));
	
	nRet = data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), data_control_sql_unregister_response_cb(g_stSqlProvider);bundle_free(pstData));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		bundle_free(pstData);
		return 1;
	}
	if (strcmp(g_szWordDesc, DUMMYGETVALUE))
	{
		FPRINTF("[Line : %d][%s] Insert data and get data mismatch, Inserted Data: %s Get Data: %s\\n", __LINE__, API_NAMESPACE, DUMMYVALUE, g_szWordDesc);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		bundle_free(pstData);
		return 1;
	}

	g_bCallbackHit = false;
	nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_delete", DataControlGetError(nRet), data_control_sql_unregister_response_cb(g_stSqlProvider);bundle_free(pstData));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		bundle_free(pstData);
		return 1;
	}

	// Target API
	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet), bundle_free(pstData));

	bundle_free(pstData);

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_insert_delete_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Insert and delete a sql entry
* @scenario				Insert Entry\n
*						Delete Entry
* @apicovered			data_control_sql_insert, data_control_sql_delete
* @passcase				When data_control_sql_insert and data_control_sql_delete are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_insert and data_control_sql_delete
//& type: auto
int ITc_data_control_sql_data_control_sql_insert_delete_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));

	// Target API
	nRet = data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}
	
	if (strcmp(g_szWordDesc, DUMMYGETVALUE))
	{
		FPRINTF("[Line : %d][%s] Insert data and get data mismatch, Inserted Data: %s Get Data: %s\\n", __LINE__, API_NAMESPACE, DUMMYVALUE, g_szWordDesc);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	g_bCallbackHit = false;

	// Target API
	nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_delete", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_free(pstData);
	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_update_select_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Update and select a sql entry
* @scenario				Update Entry\n
*						Select Entry
* @apicovered			data_control_sql_update, data_control_sql_select
* @passcase				When data_control_sql_update and data_control_sql_select are successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_update and data_control_sql_select
//& type: auto
int ITc_data_control_sql_data_control_sql_update_select_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.update_cb = DataControlSqlUpdateResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");

	bundle *pstNewData = bundle_create();
	if ( pstNewData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_add_str(pstNewData, DUMMYKEY, DUMMYVALUENEW);

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	nRet = data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(pstNewData);bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstNewData);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}
	if (strcmp(g_szWordDesc, DUMMYGETVALUE))
	{
		FPRINTF("[Line : %d][%s] Insert data and get data mismatch, Inserted Data: %s Get Data: %s\\n", __LINE__, API_NAMESPACE, DUMMYVALUE, g_szWordDesc);
		bundle_free(pstNewData);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	g_bCallbackHit = false;
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));
	// Target API
	nRet = data_control_sql_update(g_stSqlProvider, pstNewData, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_update", DataControlGetError(nRet), bundle_free(pstNewData);bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstNewData);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	if (strcmp(g_szWordDesc, DUMMYGETVALUENEW))
	{
		FPRINTF("[Line : %d][%s] Update data and get data mismatch, Updated Data: %s Get Data: %s\\n", __LINE__, API_NAMESPACE, DUMMYGETVALUENEW, g_szWordDesc);
		bundle_free(pstNewData);
		bundle_free(pstData);
		nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
		PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_delete", DataControlGetError(nRet),data_control_sql_unregister_response_cb(g_stSqlProvider));
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	g_bCallbackHit = false;
	nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_delete", DataControlGetError(nRet), bundle_free(pstNewData);bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstNewData);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_free(pstNewData);
	bundle_free(pstData);
	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_select_with_page_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Select a sql entry
* @scenario				Select Entry
* @apicovered			data_control_sql_select_with_page
* @passcase				When data_control_sql_select_with_page is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_select_with_page
//& type: auto
int ITc_data_control_sql_data_control_sql_select_with_page_p(void)
{
	START_TEST;

	int nRequestId = 0;
	int nTimeoutId = 0;

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid=1");
	const char *pszOrder = "WORD ASC";
	char *pszKey = DUMMYKEY;

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));
	nRet = data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	if (strcmp(g_szWordDesc, DUMMYGETVALUE))
	{
		FPRINTF("[Line : %d][%s] Insert data and get data mismatch, Inserted Data: %s Get Data: %s\\n", __LINE__, API_NAMESPACE, DUMMYVALUE, g_szWordDesc);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}
	
	g_bCallbackHit = false;
	// Target API
	nRet = data_control_sql_select_with_page(g_stSqlProvider, &pszKey, 1, g_szWhere, pszOrder, 1, 1, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_select_with_page", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	g_bCallbackHit = false;
	nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_delete", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		bundle_free(pstData);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	bundle_free(pstData);
	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_blob_data_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_blob_data
* @scenario				Call data_control_sql_get_blob_data
* @apicovered			data_control_sql_get_blob_data
* @passcase				When data_control_sql_get_blob_data is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_blob_data
//& type: auto
int ITc_data_control_sql_data_control_sql_get_blob_data_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectBlobResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_int_data_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_int_data
* @scenario				Call data_control_sql_get_int_data
* @apicovered			data_control_sql_get_int_data
* @passcase				When data_control_sql_get_int_data is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_int_data
//& type: auto
int ITc_data_control_sql_data_control_sql_get_int_data_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectIntResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_int64_data_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_int64_data
* @scenario				Call data_control_sql_get_int64_data
* @apicovered			data_control_sql_get_int64_data
* @passcase				When data_control_sql_get_int64_data is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_int64_data
//& type: auto
int ITc_data_control_sql_data_control_sql_get_int64_data_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectInt64ResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_text_data_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_text_data
* @scenario				Call data_control_sql_get_text_data
* @apicovered			data_control_sql_get_text_data
* @passcase				When data_control_sql_get_text_data is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_text_data
//& type: auto
int ITc_data_control_sql_data_control_sql_get_text_data_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectTextResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_double_data_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_double_data
* @scenario				Call data_control_sql_get_double_data
* @apicovered			data_control_sql_get_double_data
* @passcase				When data_control_sql_get_double_data is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_double_data
//& type: auto
int ITc_data_control_sql_data_control_sql_get_double_data_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectDoubleResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_column_count_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_column_count
* @scenario				Call data_control_sql_get_column_count
* @apicovered			data_control_sql_get_column_count
* @passcase				When data_control_sql_get_column_count is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_column_count
//& type: auto
int ITc_data_control_sql_data_control_sql_get_column_count_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnCountResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_column_item_size_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_column_item_size
* @scenario				Call data_control_sql_get_column_item_size
* @apicovered			data_control_sql_get_column_item_size
* @passcase				When data_control_sql_get_column_item_size is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_column_item_size
//& type: auto
int ITc_data_control_sql_data_control_sql_get_column_item_size_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnSizeResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	if ( bResult == false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}
	bResult = DataControlRemoveSqlData();
	if ( bResult == false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_column_item_type_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_column_item_type
* @scenario				Call data_control_sql_get_column_item_type
* @apicovered			data_control_sql_get_column_item_type
* @passcase				When data_control_sql_get_column_item_type is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_column_item_type
//& type: auto
int ITc_data_control_sql_data_control_sql_get_column_item_type_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnTypeResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_get_column_name_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_get_column_name
* @scenario				Call data_control_sql_get_column_name
* @apicovered			data_control_sql_get_column_name
* @passcase				When data_control_sql_get_column_name is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_get_column_name
//& type: auto
int ITc_data_control_sql_data_control_sql_get_column_name_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnNameResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}


/**
* @testcase 			ITc_data_control_sql_data_control_sql_step_first_last_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_step_first and data_control_sql_step_last
* @scenario				Call data_control_sql_step_first\n
*						Call data_control_sql_step_last
* @apicovered			data_control_sql_step_first, data_control_sql_step_last
* @passcase				When data_control_sql_step_first and data_control_sql_step_last is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_step_first and data_control_sql_step_last
//& type: auto
int ITc_data_control_sql_data_control_sql_step_first_last_p(void)
{
	START_TEST;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnStepFirstLastResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bool bResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	if ( bResult == false || bDelResult ==false )
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}

/**
* @testcase 			ITc_data_control_sql_data_control_sql_step_next_previous_p
* @since_tizen 			2.3
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type 				auto
* @description			Test data_control_sql_step_next and data_control_sql_step_previous
* @scenario				Call data_control_sql_step_next\n
*						Call data_control_sql_step_previous
* @apicovered			data_control_sql_step_next, data_control_sql_step_previous
* @passcase				When data_control_sql_step_next and data_control_sql_step_previous is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_sql_step_next and data_control_sql_step_previous
//& type: auto
int ITc_data_control_sql_data_control_sql_step_next_previous_p(void)
{
	START_TEST;

	int nRequestId = 0;

	g_stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	g_stSqlCallBack.select_cb = DataControlSqlSelectColoumnStepNextPreviousResponseCb;
	g_stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;

	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &g_stSqlCallBack, TESTSTRING);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet));

	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}
	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);

	data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	bundle_free(pstData);

	bool bInsertSelectResult = DataControlInsertSelectSqlData();
	bool bDelResult = DataControlRemoveSqlData();
	
	if ( bInsertSelectResult == false || bDelResult == false)
	{
		data_control_sql_unregister_response_cb(g_stSqlProvider);
		return 1;
	}

	nRet = data_control_sql_unregister_response_cb(g_stSqlProvider);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_unregister_response_cb", DataControlGetError(nRet));

	return 0;
}
/** @} */
/** @} */
