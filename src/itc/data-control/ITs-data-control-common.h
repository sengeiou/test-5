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
#ifndef _ITS_DATA_CONTROL_COMMON_H_
#define _ITS_DATA_CONTROL_COMMON_H_

#include "tct_common.h"
#include "tct_app_common.h"

//Add test package related includes here
#include <fcntl.h>
#include <data_control.h>
#include <data_control_sql.h>
#include <data_control_map.h>
#include <data_control_noti.h>
#include <string.h>
//#include <data_control_types.h>
#include <data_control_provider.h>
#include <glib.h>
#include <dlog.h>
/** @addtogroup itc-data-control
*  @ingroup itc
*  @{
*/

#define API_NAMESPACE			"DATA_CONTROL_ITC"
#define MICROSECONDS_PER_SECOND	1000000
#define MINCOUNT				1
#define TESTSTRINGSIZE			120*sizeof(char)
#define TESTVALUE				50
#define TESTSTRING				"TestString"
#define INTERNETWAITTIME		30
#define TIMEOUT_CB				150000
#define SQLPROVIDERID			"http://tizen.org/datacontrol/provider/datacontrolprovider"
#define SQLDATAID				"SqlRepository"
#define MAPPROVIDERID			"http://tizen.org/datacontrol/provider/datacontrolprovider"
#define MAPDATAID				"MapRepository"
#define MAPPROVIDERIDBULK		"http://datacontrolmapprovider.com/datacontrol/provider/datacontrolmapprovider"
#define MAPDATAIDBULK			"Dictionary"
#define DUMMYKEY				"WORD"
#define DUMMYVALUE				"'TestValue'"
#define DUMMYGETVALUE			"TestValue"
#define DUMMYVALUENEW			"'TestValueNew'"
#define DUMMYGETVALUENEW		"TestValueNew"
#define DUMMYVALUELENGTH		20
#define ERRORSTRING				"Error Sent"
#define QUERYSIZE				40
#define BLOBCOLOUMN				0
#define STRINGCOLOUMN			1
#define INTEGERCOLOUMN			3
#define DOUBLECOLOUMN			4
#define TEST_DATACONTROL_APPID	"org.tizen.datacontrolprovider"
#define TEST_DATACONTROLNOT_APPID	"org.tizen.datacontrolnotiprovider"

#define PROVIDER_ID "http://tizen.org/datacontrol/provider/datacontrolprovider"
#define SQL_DATA_ID "SqlRepository"

#define PROVIDER_ID_NOT "http://datacontrolnotiprovider.com/datacontrol/provider/datacontrolnotiprovider"
#define SQL_DATA_ID_NOT "Dictionary"

bool g_bDataControlCreation;
bool g_bCallbackHit;
bool g_bDataChangeCallbackHit;
bool g_bAddCallbackResult;
bool g_bIsInsertDataCheck;
bool g_bIsRemoveDataCheck;
char g_szWordDesc[DUMMYVALUELENGTH];
GMainLoop *g_pDataControlMainLoop;
data_control_h g_stSqlProvider;
data_control_h g_stSqlNotiProvider;
data_control_h g_stMapProvider;

data_control_h g_stSqlProviderForBind;
data_control_h g_stMapProviderForBind;
bool g_bCheckHandleId;
bool g_bCheckHandleIdForBind;
int g_nProviderHandleId;
int g_nProviderHandleIdForBind;

int g_nRequestId;
long long g_nRowId;
void *g_pDbHandle;
char **g_pResultList;
int g_nResultCount;
bundle *g_pstData;
char g_szWhere[QUERYSIZE];

data_control_sql_response_cb g_stSqlCallBack;

#define START_TEST {\
	FPRINTF("[Line : %d][%s] Starting test : %s\\n", __LINE__, API_NAMESPACE, __FUNCTION__);\
	if ( !g_bDataControlCreation )\
{\
	FPRINTF("[Line : %d][%s] Precondition of data_control failed so leaving test\\n", __LINE__, API_NAMESPACE);\
	return 1;\
}\
}

#define RUN_POLLING_LOOP {\
	if ( !g_bCallbackHit )\
{\
	g_pDataControlMainLoop = g_main_loop_new(NULL, false);\
	int nTimeoutId = g_timeout_add(TIMEOUT_CB, DataControlTimeout, g_pDataControlMainLoop);\
	g_main_loop_run(g_pDataControlMainLoop);\
	g_source_remove(nTimeoutId);\
	g_pDataControlMainLoop = NULL;\
}\
}
int __result;
#define normal_exit(result) do { \
	__result = result; \
	ui_app_exit(); \
	g_bAddCallbackResult = true; \
} while (0)

#define CHECK_HANDLE_CLEANUP(Handle, API, FreeResource) {\
	if (  Handle == NULL )\
	{\
		FPRINTF("[Line : %d][%s] %s failed, error returned = Handle returned is NULL\\n", __LINE__, API_NAMESPACE, API);\
		FreeResource;\
		return 1;\
	}\
}

//Add helper function declarations here

char* DataControlGetError(int nRet);
gboolean DataControlTimeout(gpointer data);
bool DataControlInitiateSqlHandle(data_control_h *stSqlProvider);
bool DataControlInitiateMapHandle(data_control_h *stMapProvider);
bool DataControlNotiSqlHandle(data_control_h *stSqlProvider);
bool DataControlInsertSelectSqlData(void);
bool DataControlRemoveSqlData(void);
bool DataControlInitiateMapBulkHandle(data_control_h *stMapProvider);
bool DataControlInitiateSqlBulkHandle(data_control_h *stSqlProvider);
/** @} */
#endif  //_ITS_DATA_CONTROL_COMMON_H_
