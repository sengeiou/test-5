#include "CTs-platform-permission-common.h"
#include <data_control.h>
#include <data_control_sql.h>
#include <data_control_map.h>
#include <data_control_provider.h>
#include <data_control_noti.h>
#define SQLDATAID				"SqlRepository"
#define MAPDATAID				"MapRepository"
#define PROVIDERID				"http://tizen.org/datacontrol/provider/datacontrolprovider"
#define TESTINGSTRING				"TestString"
#define SQLPROVIDERID			"http://tizen.org/datacontrol/provider/datacontrolprovider"
#define DUMMYKEY				"WORD"
#define DUMMYVALUE				"'TestValue'"
#define DUMMYGETVALUE			"TestValue"
#define DUMMYVALUELENGTH		20
#define QUERYSIZE				40
#define BLOBCOLOUMN				0
#define TESTSTRINGSIZE			120*sizeof(char)
#define INTEGERCOLOUMN			3
#define TIMEOUT_CB				10000
#define DUMMYVALUENEW			"'TestValueNew'"
#define MAPPROVIDERID			"http://tizen.org/datacontrol/provider/datacontrolprovider"

bool g_bDataControlCreation;
bool g_bCallbackHit;
bool g_bIsInsertDataCheck;
bool g_bDataChangeCallbackHit;
bool g_bAddCallbackResult;
bool g_bIsRemoveDataCheck;
char g_szWordDesc[DUMMYVALUELENGTH];
GMainLoop *g_pDataControlMainLoop;
data_control_h g_stSqlProvider;
data_control_h g_stMapProvider;
int g_nRequestId;
long long g_nRowId;
void *g_pDbHandle;
char **g_pResultList;
int g_nResultCount;
bundle *g_pstData;
char g_szWhere[QUERYSIZE];

data_control_sql_response_cb g_stSqlCallBack;
data_control_h g_stSqlProvider;
data_control_h g_stMapProvider;
bool g_bCallbackHit;

#define RUN_POLLING_LOOP {\
	if ( !g_bCallbackHit )\
{\
	g_pDataControlMainLoop = g_main_loop_new(NULL, false);\
	nTimeoutId = g_timeout_add(TIMEOUT_CB, DataControlTimeout, g_pDataControlMainLoop);\
	g_main_loop_run(g_pDataControlMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pDataControlMainLoop = NULL;\
}\
}

/**
* @function 		DataControlGetError
* @description	 	Maps error enumerators to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* DataControlGetError(int nRet)
{
	char *szErrorVal = NULL;

	switch ( nRet )
	{
	case DATA_CONTROL_ERROR_NONE:			szErrorVal = "DATA_CONTROL_ERROR_NONE";			break;
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
* @function 		DataControlInitiateMapHandle
* @description	 	Initiate map handle
* @parameter		[stMapProvider] Handle Pointer
* @return 			NA
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
* @function 		CTs_platform_permission_datacontrol_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_datacontrol_startup(void)
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
* @function 		CTs_platform_permission_datacontrol_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_datacontrol_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function 		DataControlInitiateSqlHandle
* @description	 	Initiate sql handle
* @parameter		[stSqlProvider] Handle Pointer
* @return 			NA
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
		nRet = data_control_sql_set_provider_id(*stSqlProvider, SQLPROVIDERID);
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

static void DataControlProviderSqlInsertCb(int request_id, data_control_h provider, bundle *insert_data, void *user_data)
{
#if DEBUG
FPRINTF("[Line : %d][%s] DataControlProviderSqlInsertCb callback called\\n", __LINE__, API_NAMESPACE);
#endif

	g_nRequestId = request_id;
	g_bCallbackHit = true;
	
	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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
	
	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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
	
	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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
* @function 		DataControlAddCallbackResultCB
* @description	 	Called when the consumer receives the result of the data change callback adding operation.
* @parameter		data_control_h provider, data_control_error_e result, int callback_id, void *user_data
* @return 			NA
*/
static void DataControlAddCallbackResultCB( data_control_h provider, data_control_error_e result, int callback_id,	void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlAddCallbackResultCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
FPRINTF("[Line : %d][%s] DataControlAddCallbackResultCB callback called\\n", __LINE__, API_NAMESPACE);
	g_bAddCallbackResult = true;
	
	if ( g_pDataControlMainLoop )
	{
		g_main_loop_quit(g_pDataControlMainLoop);
	}
	return;
}
/**
* @function 		DataControlDataChangeCB
* @description	 	Called when received data changed notification from provider application.
* @parameter		data_control_h provider, data_control_data_change_type_e type, bundle *data, void *user_data
* @return 			NA
*/
static void DataControlDataChangeCB(data_control_h provider, data_control_data_change_type_e type, bundle *data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlDataChangeCB callback called\\n", __LINE__, API_NAMESPACE);
#endif
FPRINTF("[Line : %d][%s] DataControlDataChangeCB callback called\\n", __LINE__, API_NAMESPACE);
	g_bDataChangeCallbackHit = true;

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
	
	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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

//& set: DataControl
/*******************************************************************************CallBack Functions********************************************************/
/**
* @function 		DataControlSqlInsertResponseCb
* @description	 	Called when record is inserted
* @parameter		int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data
* @return 			NA
*/
static int DataControlSqlInsertResponseCb(int request_id, data_control_h provider, long long inserted_row_id, bool provider_result, const char *error, void *user_data) 
{
#if DEBUG
	FPRINTF("[Line : %d][%s] DataControlSqlInsertResponseCb callback called\\n", __LINE__, API_NAMESPACE);
#endif
	
	return 0;
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

	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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
	
	if(strcmp((char*)user_data,TESTINGSTRING) != 0)
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
* @function 		DataControlTimeout
* @description	 	Called if some callback is not invoked for a particular timeout
* @parameter		gpointer data
* @return 			gboolean
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
//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase			CTc_DataControl_PrivilegeDataControlConsumer_map_add
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a provider handle\n
* 					Sets the Provider ID\n
* 					Sets the Data ID\n
* 					Adds the value associated with the specified key to the key-values map owned by the key-value structured data control provider\n
* 					Removes the value associated with the specified key from the key-values map owned by the key-value structured data control provider\n
* 					Destroys the provider handle and releases all its resources\n
* @apicovered		data_control_map_create, data_control_map_add and data_control_map_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition		NA
* @postcondition	NA
*/
int CTc_DataControl_PrivilegeDataControlConsumer_map_add(void)
{
	START_TEST;

	char *pszDataId = "table";
	data_control_h hDataControl = NULL;
	const char *pszKey = "WORD";
	const char *pszValue = "'TestValue'";
	int nRequestId = 0;

	int nRet = data_control_map_create(&hDataControl);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));

	nRet = data_control_map_set_provider_id (hDataControl, PROVIDERID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_set_data_id (hDataControl, pszDataId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	nRet = data_control_map_add(hDataControl, pszKey, pszValue, &nRequestId);
	if(nRet ==DATA_CONTROL_ERROR_NONE)
	{
		data_control_map_remove(hDataControl, pszKey, pszValue, &nRequestId);
	}
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_map_add", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	data_control_map_destroy(hDataControl);
	
	return 0;
}

//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase			CTc_DataControl_PrivilegeDataControlConsumer_map_get
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a provider handle\n
* 					Sets the Provider ID\n
* 					Sets the Data ID\n
* 					Adds the value associated with the specified key to the key-values map owned by the key-value structured data control provider\n
* 					Removes the value associated with the specified key from the key-values map owned by the key-value structured data control provider\n
* 					Destroys the provider handle and releases all its resources\n
* @apicovered		data_control_map_create,data_control_map_remove and data_control_map_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition		NA
* @postcondition	NA
*/

int CTc_DataControl_PrivilegeDataControlConsumer_map_get(void)
{
	START_TEST;

	char *pszDataId = "table";
	data_control_h hDataControl = NULL;
	int nRequestId = 0;


	int nRet = data_control_map_create(&hDataControl);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));

	nRet = data_control_map_set_provider_id (hDataControl, PROVIDERID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_set_data_id (hDataControl, pszDataId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_get(hDataControl, DUMMYKEY, &nRequestId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_map_get", DataControlGetError(nRet), data_control_map_destroy(hDataControl));
	
	data_control_map_destroy(hDataControl);
	
	return 0;
}

//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase			CTc_DataControl_PrivilegeDataControlConsumer_map_get_with_page
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a provider handle\n
* 					Sets the Provider ID\n
* 					Sets the Data ID\n
* 					Adds the value associated with the specified key to the key-values map owned by the key-value structured data control provider\n
* 					Removes the value associated with the specified key from the key-values map owned by the key-value structured data control provider\n
* 					Destroys the provider handle and releases all its resources\n
* @apicovered		data_control_map_create,data_control_map_get_with_page and data_control_map_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition		NA
* @postcondition	NA
*/
int CTc_DataControl_PrivilegeDataControlConsumer_map_get_with_page(void)
{
	START_TEST;

	char *pszDataId = "table";
	data_control_h hDataControl = NULL;
	const char *pszKey = "WORD";
	int nRequestId = 0;

	int nRet = data_control_map_create(&hDataControl);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));

	nRet = data_control_map_set_provider_id (hDataControl, PROVIDERID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_set_data_id (hDataControl, pszDataId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_get_with_page(hDataControl, pszKey, &nRequestId, 1, 1);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_map_get_with_page", DataControlGetError(nRet), data_control_map_destroy(hDataControl));
	
	data_control_map_destroy(hDataControl);
	
	return 0;
}
//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase			CTc_DataControl_PrivilegeDataControlConsumer_map_set
* @since_tizen		2.3
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Creates a provider handle\n
* 					Sets the Provider ID\n
* 					Sets the Data ID\n
* 					Adds the value associated with the specified key to the key-values map owned by the key-value structured data control provider\n
* 					Removes the value associated with the specified key from the key-values map owned by the key-value structured data control provider\n
* 					Destroys the provider handle and releases all its resources\n
* @apicovered		data_control_map_create,data_control_map_set and data_control_map_destroy
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition		NA
* @postcondition	NA
*/
int CTc_DataControl_PrivilegeDataControlConsumer_map_set(void)
{
	START_TEST;

	char *pszDataId = "table";
	data_control_h hDataControl = NULL;
	const char *pszKey = "WORD";
	const char *pszValue = "'TestValue'";
	int nRequestId = 0;

	const char *pszNewValue = DUMMYVALUENEW;

	int nRet = data_control_map_create(&hDataControl);
	PRINT_RESULT(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_create", DataControlGetError(nRet));

	nRet = data_control_map_set_provider_id (hDataControl, PROVIDERID);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_provider_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_set_data_id (hDataControl, pszDataId);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_map_set_data_id", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	
	nRet = data_control_map_set(hDataControl, pszKey, pszValue, pszNewValue, &nRequestId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_map_set", DataControlGetError(nRet), data_control_map_destroy(hDataControl));

	nRet = data_control_map_destroy(hDataControl);
	
	return 0;
}

//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlConsumer_map_register_cb
* @since_tizen 			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test data_control_provider_map_register_cb and data_control_provider_map_unregister_cb
* @scenario				Call data_control_provider_map_register_cb\n
*						Call data_control_provider_map_unregister_cb
* @apicovered			data_control_provider_map_register_cb, data_control_provider_map_unregister_cb
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			None
* @postcondition		None
*/

int CTc_DataControl_PrivilegeDataControlConsumer_map_register_cb(void)
{
	START_TEST;

	data_control_provider_map_cb stMapCallBack = {0};
	stMapCallBack.add_cb = DataControlProviderMapInsertCb;
	stMapCallBack.remove_cb = DataControlProviderMapRemoveCb;

	// Target API
	int nRet = data_control_provider_map_register_cb(&stMapCallBack, TESTINGSTRING);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_provider_map_register_cb", DataControlGetError(nRet),data_control_provider_map_unregister_cb(),DATA_CONTROL_ERROR_NONE);

	return 0;
}

//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlConsumer_sql_insert_cb
* @since_tizen 			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test data_control_sql_register_response_cb and data_control_sql_unregister_response_cb
* @scenario				Call data_control_sql_register_response_cb\n
*						Call data_control_sql_unregister_response_cb
* @apicovered			data_control_sql_register_response_cb, data_control_sql_unregister_response_cb
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			None
* @postcondition		None
*/

int CTc_DataControl_PrivilegeDataControlConsumer_sql_insert_cb(void)
{
	START_TEST;

	int nRequestId = 0;
	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
		{
			g_bDataControlCreation = true;
		}
	}
	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, strlen("rowid=1")+1, "rowid=1");

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;
	
	// Target API
	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTINGSTRING);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet), bundle_free(pstData));

	g_bCallbackHit = false;
	g_bIsInsertDataCheck = true;
	memset(g_szWordDesc, 0, sizeof(g_szWordDesc));
	
	nRet = data_control_sql_insert(g_stSqlProvider, pstData, &nRequestId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_sql_insert", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));

	data_control_sql_unregister_response_cb(g_stSqlProvider);
	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_stSqlProvider);
	}
	bundle_free(pstData);

	return 0;
}

//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlConsumer_sql_insert_delete_cb
* @since_tizen 			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test data_control_sql_register_response_cb and data_control_sql_unregister_response_cb
* @scenario				Call data_control_sql_register_response_cb\n
*						Call data_control_sql_unregister_response_cb
* @apicovered			data_control_sql_register_response_cb, data_control_sql_unregister_response_cb
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			None
* @postcondition		None
*/

int CTc_DataControl_PrivilegeDataControlConsumer_data_control_sql_update(void)
{
	START_TEST;

	int nRequestId = 0;
	
	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
		{
			g_bDataControlCreation = true;
		}
	}
	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}
	

	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, strlen("rowid=1")+1, "rowid=1");

	data_control_sql_response_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlSqlInsertResponseCb;
	stSqlCallBack.delete_cb = DataControlSqlRemoveResponseCb;
	stSqlCallBack.select_cb = DataControlSqlSelectResponseCb;
	
	// Target API
	int nRet = data_control_sql_register_response_cb(g_stSqlProvider, &stSqlCallBack, TESTINGSTRING);
	PRINT_RESULT_CLEANUP(DATA_CONTROL_ERROR_NONE, nRet, "data_control_sql_register_response_cb", DataControlGetError(nRet), bundle_free(pstData));
	bundle *pstNewData = bundle_create();
	
	nRet = data_control_sql_update(g_stSqlProvider, pstNewData, g_szWhere, &nRequestId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_sql_update", DataControlGetError(nRet), bundle_free(pstData);data_control_sql_unregister_response_cb(g_stSqlProvider));
	
	data_control_sql_unregister_response_cb(g_stSqlProvider);
	bundle_free(pstData);
	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_stSqlProvider);
	}

	return 0;
}
//& purpose: check privilege http://tizen.org/privilege/datasharing
//& type: auto
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlConsumer_provider_sql_register_cb
* @since_tizen 			2.3
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test data_control_provider_sql_register_cb and data_control_provider_sql_unregister_cb
* @scenario				Call data_control_provider_sql_register_cb\n
*						Call data_control_provider_sql_unregister_cb
* @apicovered			data_control_provider_sql_register_cb, data_control_provider_sql_unregister_cb
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED or non-privileged precondition api does not return error none value
* @precondition			None
* @postcondition		None
*/

int CTc_DataControl_PrivilegeDataControlConsumer_provider_sql_register_cb(void)
{
	START_TEST;

	data_control_provider_sql_cb stSqlCallBack = {0};
	stSqlCallBack.insert_cb = DataControlProviderSqlInsertCb;
	stSqlCallBack.delete_cb = DataControlProviderSqlRemoveCb;

	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
		{
			g_bDataControlCreation = true;
		}
	}
	// Target API
	int nRet = data_control_provider_sql_register_cb(&stSqlCallBack, TESTINGSTRING);
	PRINT_RESULT_ERROR_NONE(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_provider_sql_register_cb", DataControlGetError(nRet),data_control_provider_sql_unregister_cb(),DATA_CONTROL_ERROR_NONE);

	data_control_provider_sql_unregister_cb();
	if ( g_bDataControlCreation == true )
	{
		data_control_sql_destroy(g_stSqlProvider);
	}
	
	return 0;
}
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlprovider_add_cb
* @since_tizen 			3.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sends a data change notification to consumer applications which have successfully added a data change callback.
* @scenario				Call data_control_provider_send_data_change_noti
* @apicovered			data_control_provider_send_data_change_noti
* @passcase				When data_control_provider_send_data_change_noti is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_match_provider_id
//& type: auto
int CTc_DataControl_PrivilegeDataControlprovider_add_cb(void)
{
	START_TEST;

	int pCallbackId = -1;
	int nTimeoutId = 0 ;
	g_bDataChangeCallbackHit = false;
	g_bAddCallbackResult = false;

	bundle *pBundleData = bundle_create();
	if ( pBundleData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}

	// Target API
	int nRet = data_control_add_data_change_cb(g_stSqlProvider, DataControlDataChangeCB, NULL, DataControlAddCallbackResultCB, NULL, &pCallbackId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_add_data_change_cb", DataControlGetError(nRet),bundle_free(pBundleData));
	bundle_free(pBundleData);
	return 0;
}
/**
* @testcase 			CTc_DataControl_PrivilegeDataControlprovider_send_data_change_noti
* @since_tizen 			3.0
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Sends a data change notification to consumer applications which have successfully added a data change callback.
* @scenario				Call data_control_provider_send_data_change_noti
* @apicovered			data_control_provider_send_data_change_noti
* @passcase				When data_control_provider_send_data_change_noti is successful
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: API to test data_control_provider_match_provider_id
//& type: auto
int CTc_DataControl_PrivilegeDataControlprovider_send_data_change_noti(void)
{
	START_TEST;

	int pCallbackId = -1;
	int nTimeoutId = 0 ;
	g_bDataChangeCallbackHit = false;
	int nRequestId = 0;

	if ( DataControlInitiateSqlHandle(&g_stSqlProvider) == true )
	{
		if ( DataControlInitiateMapHandle(&g_stMapProvider) == true )
		{
			g_bDataControlCreation = true;
		}
	}
	bundle *pstData = bundle_create();
	if ( pstData == NULL )
	{
		FPRINTF("[Line : %d][%s] bundle_create failed\\n", __LINE__, API_NAMESPACE);
		return 1;
	}


	bundle_add_str(pstData, DUMMYKEY, DUMMYVALUE);
	memset(g_szWhere, 0, QUERYSIZE);
	snprintf(g_szWhere, strlen("rowid=1")+1, "rowid=1");
	g_bAddCallbackResult = false;


	int nRet = data_control_provider_send_data_change_noti( g_stSqlProvider, DATA_CONTROL_DATA_CHANGE_SQL_INSERT, pstData);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "data_control_provider_send_data_change_noti", DataControlGetError(nRet),bundle_free(pstData));
	bundle_free(pstData);
	return 0;
}
