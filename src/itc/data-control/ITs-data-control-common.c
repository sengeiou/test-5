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
//Add helper function definitions here

/**
* @function			DataControlGetError
* @description		Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* DataControlGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case DATA_CONTROL_ERROR_OUT_OF_MEMORY:			szErrorVal = "DATA_CONTROL_ERROR_OUT_OF_MEMORY";			break;
	case DATA_CONTROL_ERROR_IO_ERROR:				szErrorVal = "DATA_CONTROL_ERROR_IO_ERROR";					break;
	case DATA_CONTROL_ERROR_INVALID_PARAMETER:		szErrorVal = "DATA_CONTROL_ERROR_INVALID_PARAMETER";		break;
	case DATA_CONTROL_ERROR_PERMISSION_DENIED:		szErrorVal = "DATA_CONTROL_ERROR_PERMISSION_DENIED";		break;
	case DATA_CONTROL_ERROR_MAX_EXCEEDED:			szErrorVal = "DATA_CONTROL_ERROR_MAX_EXCEEDED";				break;
	default:										szErrorVal = "Unknown Error";								break;
	}
	return szErrorVal;
}

/**
* @function			DataControlTimeout
* @description		Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return			gboolean
*/
gboolean DataControlTimeout(gpointer data)
{
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	FPRINTF("[Line : %d][%s] Callback Timeout\\n", __LINE__, API_NAMESPACE);
	return false;
}

/**
* @function			DataControlInitiateSqlHandle
* @description		Initiate sql handle
* @parameter		[stSqlProvider] Handle Pointer
* @return			NA
*/
bool DataControlInitiateSqlHandle(data_control_h *stSqlProvider)
{
	int nRet = data_control_sql_create(stSqlProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_create", DataControlGetError(nRet));

	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		return false;
	}
	else
	{
		nRet = data_control_sql_set_provider_id(*stSqlProvider,SQLPROVIDERID );
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_provider_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}
		nRet = data_control_sql_set_data_id(*stSqlProvider, SQLDATAID);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_data_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}
	}
	return true;
}

/**
* @function			DataControlNotiSqlHandle
* @description		Initiate sql handle
* @parameter		[stSqlProvider] Handle Pointer
* @return			NA
*/
bool DataControlNotiSqlHandle(data_control_h *stSqlProvider)
{
	int nRet = data_control_sql_create(stSqlProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_create", DataControlGetError(nRet));

	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		return false;
	}
	else
	{
		nRet = data_control_sql_set_provider_id(*stSqlProvider, PROVIDER_ID_NOT);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_provider_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}
		nRet = data_control_sql_set_data_id(*stSqlProvider,SQL_DATA_ID_NOT );
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_data_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}
	}
	return true;
}

/**
* @function			DataControlInitiateMapHandle
* @description		Initiate map handle
* @parameter		[stMapProvider] Handle Pointer
* @return			NA
*/
bool DataControlInitiateMapHandle(data_control_h *stMapProvider)
{
	int nRet = data_control_map_create(stMapProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));
	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		return false;
	}
	else
	{
		nRet = data_control_map_set_provider_id(*stMapProvider, MAPPROVIDERID);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}
		nRet = data_control_map_set_data_id(*stMapProvider, MAPDATAID);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}
	}
	return true;
}


/**
* @function			DataControlInitiateMapBulkHandle
* @description		Initiate map handle
* @parameter		[stMapProvider] Handle Pointer
* @return			NA
*/
bool DataControlInitiateMapBulkHandle(data_control_h *stMapProvider)
{
	int nRet = data_control_map_create(stMapProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));

	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		return false;
	}
	else if(stMapProvider == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "data_control_map_create");
		return false;
	}
	else
	{
		nRet = data_control_map_set_provider_id(*stMapProvider, MAPPROVIDERIDBULK);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}

		char *getId = NULL;
		nRet = data_control_map_get_provider_id(*stMapProvider, &getId);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_provider_id", DataControlGetError(nRet));

		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}
		else if(getId == NULL)
		{
			FPRINTF("[Line : %d][%s] data_control_map_get_provider_id failed as Provider Id is NULL\\n", __LINE__, API_NAMESPACE);
			data_control_map_destroy(*stMapProvider);
			return false;
		}
		else
		{
			if ( strstr(getId, MAPPROVIDERIDBULK) == NULL )
			{
				FPRINTF("[Line : %d][%s] data_control_map_get_provider_id failed as Provider Id not found\\n", __LINE__, API_NAMESPACE);
				FREE_MEMORY(getId);
				data_control_map_destroy(*stMapProvider);
				return false;
			}

			FREE_MEMORY(getId);
		}

		nRet = data_control_map_set_data_id(*stMapProvider, MAPDATAIDBULK);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}

		char *getProId = NULL;

		nRet = data_control_map_get_data_id(*stMapProvider, &getProId);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_get_data_id", DataControlGetError(nRet));

		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stMapProvider);
			return false;
		}
		else if(getProId == NULL)
		{
			FPRINTF("[Line : %d][%s] data_control_map_get_data_id failed as Data Id is NULL\\n", __LINE__, API_NAMESPACE);
			data_control_map_destroy(*stMapProvider);
			return false;
		}
		else
		{
			if ( strstr(getProId, MAPDATAIDBULK) == NULL )
			{
				FPRINTF("[Line : %d][%s] data_control_map_get_data_id failed as Data Id not found\\n", __LINE__, API_NAMESPACE);
				FREE_MEMORY(getProId);
				data_control_map_destroy(*stMapProvider);
				return false;
			}

			FREE_MEMORY(getProId);
		}
	}
	return true;
}


/**
* @function			DataControlInitiateSqlBulkHandle
* @description		Initiate sql handle
* @parameter		[stSqlProvider] Handle Pointer
* @return			NA
*/
bool DataControlInitiateSqlBulkHandle(data_control_h *stSqlProvider)
{
	int nRet = data_control_sql_create(stSqlProvider);
	PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_create", DataControlGetError(nRet));

	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		return false;
	}
	else if(stSqlProvider == NULL)
	{
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, "data_control_map_create");
		return false;
	}
	else
	{
		nRet = data_control_sql_set_provider_id(*stSqlProvider, PROVIDER_ID );
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_provider_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}

		char *getId = NULL;
		nRet = data_control_sql_get_provider_id(*stSqlProvider, &getId);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_get_provider_id", DataControlGetError(nRet));

		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stSqlProvider);
			return false;
		}
		else if(getId == NULL)
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_provider_id failed as Provider Id is NULL\\n", __LINE__, API_NAMESPACE);
			data_control_map_destroy(*stSqlProvider);
			return false;
		}
		else
		{
			if ( strstr(getId, PROVIDER_ID) == NULL )
			{
				FPRINTF("[Line : %d][%s] data_control_sql_get_provider_id failed as Provider Id not found\\n", __LINE__, API_NAMESPACE);
				FREE_MEMORY(getId);
				data_control_map_destroy(*stSqlProvider);
				return false;
			}

			FREE_MEMORY(getId);
		}

		nRet = data_control_sql_set_data_id(*stSqlProvider, SQL_DATA_ID);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_set_data_id", DataControlGetError(nRet));
		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_sql_destroy(*stSqlProvider);
			return false;
		}

		char *getProId = NULL;

		nRet = data_control_sql_get_data_id(*stSqlProvider, &getProId);
		PRINT_RESULT_NORETURN(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_get_data_id", DataControlGetError(nRet));

		if ( nRet != DATA_CONTROL_ERROR_NONE )
		{
			data_control_map_destroy(*stSqlProvider);
			return false;
		}
		else if(getProId == NULL)
		{
			FPRINTF("[Line : %d][%s] data_control_sql_get_data_id failed as Data Id is NULL\\n", __LINE__, API_NAMESPACE);
			data_control_map_destroy(*stSqlProvider);
			return false;
		}
		else
		{
			if ( strstr(getProId, SQL_DATA_ID) == NULL )
			{
				FPRINTF("[Line : %d][%s] data_control_sql_get_data_id failed as Data Id not found\\n", __LINE__, API_NAMESPACE);
				FREE_MEMORY(getProId);
				data_control_map_destroy(*stSqlProvider);
				return false;
			}

			FREE_MEMORY(getProId);
		}
	}
	return true;
}

/**
* @function			DataControlInsertSelectSqlData
* @description		Insert SQL Entry
* @parameter		NA
* @return			Pass Fail Status
*/
bool DataControlInsertSelectSqlData(void)
{
	int nRet = 0;
	int nTimeoutId = 0;
	int nRequestId = 0;

	char* pszValue[5] = {0};
	pszValue[0] = "WORD";
	pszValue[1] = "WORD_DESC";
	pszValue[2] = "WORD_LEN";
	pszValue[3] = "WORD_DESC_LEN";
	pszValue[4] = "WORD_STATUS";

	char word_len[16] = {0};
	char word_desc_len[16] = {0};
	snprintf(word_len, 16, "%d", strlen("'1234'"));
	snprintf(word_desc_len, 16, "%d", strlen("'word_0 initially'") - 2);

	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, QUERYSIZE-1, "rowid<3");

	g_pstData = bundle_create();
	if ( g_pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return false;
	}
	bundle_add_str(g_pstData, "WORD", "X'1234'");
	bundle_add_str(g_pstData, "WORD_DESC", "'word_0 initially'");
	bundle_add_str(g_pstData, "WORD_LEN", word_len);
	bundle_add_str(g_pstData, "WORD_DESC_LEN", word_desc_len);
	bundle_add_str(g_pstData, "WORD_STATUS", "0.2");

	g_bCallbackHit = false;
	nRet = data_control_sql_insert(g_stSqlProvider, g_pstData, &nRequestId);
	bundle_free(g_pstData);
	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] data_control_sql_insert failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
		return false;
	}
	RUN_POLLING_LOOP;
	if ( !g_bCallbackHit )
	{
		FPRINTF("[Line : %d][%s] Failed to insert into DB, callback issue\\n", __LINE__, API_NAMESPACE);
		return false;
	}

	g_bCallbackHit = false;
	nRet = data_control_sql_select(g_stSqlProvider, pszValue, 5, g_szWhere, "WORD ASC", &nRequestId);
	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] data_control_sql_select failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
		return false;
	}
	else
	{
		RUN_POLLING_LOOP;
		if ( !g_bCallbackHit )
		{
			FPRINTF("[Line : %d][%s] Failed to complete select operation, callback issue\\n", __LINE__, API_NAMESPACE);
			return false;
		}
	}
	return true;
}

/**
* @function			DataControlRemoveSqlData
* @description		Delete SQL Entry
* @parameter		NA
* @return			Pass Fail Status
*/
bool DataControlRemoveSqlData(void)
{
	int nRet = 0;
	int nTimeoutId = 0;
	int nRequestId = 0;

	g_bCallbackHit = false;
	nRet = data_control_sql_delete(g_stSqlProvider, g_szWhere, &nRequestId);
	if ( nRet != DATA_CONTROL_ERROR_NONE )
	{
		FPRINTF("[Line : %d][%s] data_control_sql_delete failed, error returned = %s\\n", __LINE__, API_NAMESPACE, DataControlGetError(nRet));
		return false;
	}
	else
	{
		RUN_POLLING_LOOP;
		if ( !g_bCallbackHit )
		{
			FPRINTF("[Line : %d][%s] Failed to delete from DB, callback issue\\n", __LINE__, API_NAMESPACE);
		}
	}
	return true;
}
/** @} */
