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
#include "ITs-sync-manager-common.h"

//Add helper function definitions here

/** @addtogroup itc-sync-manager
*  @ingroup itc
*  @{
*/

/**
* @function			SyncManagerGetError
* @description		Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* SyncManagerGetError(int nRet)
{
	char *szErrorVal = NULL;
	switch ( nRet )
	{
		case SYNC_ERROR_NONE:						szErrorVal = "SYNC_ERROR_NONE";							break;
		case SYNC_ERROR_NOT_SUPPORTED:				szErrorVal = "SYNC_ERROR_NOT_SUPPORTED";				break;
		case SYNC_ERROR_OUT_OF_MEMORY:				szErrorVal = "SYNC_ERROR_OUT_OF_MEMORY";				break;
		case SYNC_ERROR_IO_ERROR:					szErrorVal = "SYNC_ERROR_IO_ERROR";						break;
		case SYNC_ERROR_PERMISSION_DENIED:			szErrorVal = "SYNC_ERROR_PERMISSION_DENIED";			break;
		case SYNC_ERROR_ALREADY_IN_PROGRESS:		szErrorVal = "SYNC_ERROR_ALREADY_IN_PROGRESS";			break;
		case SYNC_ERROR_INVALID_OPERATION:			szErrorVal = "SYNC_ERROR_INVALID_OPERATION";			break;
		case SYNC_ERROR_INVALID_PARAMETER:			szErrorVal = "SYNC_ERROR_INVALID_PARAMETER";			break;
		case SYNC_ERROR_UNKNOWN:					szErrorVal = "SYNC_ERROR_UNKNOWN";						break;
		case SYNC_ERROR_SYSTEM:						szErrorVal = "SYNC_ERROR_SYSTEM";						break;
		case SYNC_ERROR_QUOTA_EXCEEDED:				szErrorVal = "SYNC_ERROR_QUOTA_EXCEEDED";				break;
		case SYNC_ERROR_SYNC_ADAPTER_NOT_FOUND:		szErrorVal = "SYNC_ERROR_SYNC_ADAPTER_NOT_FOUND";		break;
		default:									szErrorVal = "SYNC_ERROR_UNKNOWN";						break;
	}

	return szErrorVal;
}

/**
* @function			AccountManagerGetError
* @description		Maps error enums to string values
* @parameter		nRet : error code returned
* @return			error string
*/
char* AccountManagerGetError(int nRet)
{
	char* szErrorVal = NULL;

	switch ( nRet )
	{
	case ACCOUNT_ERROR_NONE:						szErrorVal = "ACCOUNT_ERROR_NONE";						break;
	case ACCOUNT_ERROR_INVALID_PARAMETER:			szErrorVal = "ACCOUNT_ERROR_INVALID_PARAMETER";			break;
	case ACCOUNT_ERROR_OUT_OF_MEMORY:				szErrorVal = "ACCOUNT_ERROR_OUT_OF_MEMORY";				break;
	case ACCOUNT_ERROR_DATABASE_BUSY:				szErrorVal = "ACCOUNT_ERROR_DATABASE_BUSY";				break;
	case ACCOUNT_ERROR_DUPLICATED:					szErrorVal = "ACCOUNT_ERROR_DUPLICATED";				break;
	case ACCOUNT_ERROR_NO_DATA:						szErrorVal = "ACCOUNT_ERROR_NO_DATA";					break;
	case ACCOUNT_ERROR_RECORD_NOT_FOUND:			szErrorVal = "ACCOUNT_ERROR_RECORD_NOT_FOUND";			break;
	case ACCOUNT_ERROR_DB_FAILED:					szErrorVal = "ACCOUNT_ERROR_DB_FAILED";					break;
	case ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE:			szErrorVal = "ACCOUNT_ERROR_NOT_ALLOW_MULTIPLE";		break;
	case ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER:		szErrorVal = "ACCOUNT_ERROR_NOT_REGISTERED_PROVIDER";	break;
	case ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL:		szErrorVal = "ACCOUNT_ERROR_EVENT_SUBSCRIPTION_FAIL";	break;
	case ACCOUNT_ERROR_DB_NOT_OPENED:				szErrorVal = "ACCOUNT_ERROR_DB_NOT_OPENED";				break;
	case ACCOUNT_ERROR_QUERY_SYNTAX_ERROR:			szErrorVal = "ACCOUNT_ERROR_QUERY_SYNTAX_ERROR";		break;
	case ACCOUNT_ERROR_ITERATOR_END:				szErrorVal = "ACCOUNT_ERROR_ITERATOR_END";				break;
	case ACCOUNT_ERROR_NOTI_FAILED:					szErrorVal = "ACCOUNT_ERROR_NOTI_FAILED";				break;
	case ACCOUNT_ERROR_PERMISSION_DENIED:			szErrorVal = "ACCOUNT_ERROR_PERMISSION_DENIED";			break;
	case ACCOUNT_ERROR_XML_PARSE_FAILED:			szErrorVal = "ACCOUNT_ERROR_XML_PARSE_FAILED";			break;
	case ACCOUNT_ERROR_XML_FILE_NOT_FOUND:			szErrorVal = "ACCOUNT_ERROR_XML_FILE_NOT_FOUND";		break;
	default:										szErrorVal = "ACCOUNT_ERROR_UNKNOWN";
	}

	return szErrorVal;
}

/**
* @function			TimeoutFunction
* @description		Called if some callback is not invoked for a particular Timeout
* @parameter		gpointer data
* @return			gboolean
*/
gboolean TimeoutFunction(gpointer data)
{
	FPRINTF("[Line : %d][%s] Timeout after %d seconds\\n", __LINE__, API_NAMESPACE, TIMEOUT);
	GMainLoop *pMainLoop = NULL;
	pMainLoop = (GMainLoop *)data;
	if ( pMainLoop != NULL )
	{
		g_main_loop_quit(pMainLoop);
	}
	return false;
}

/**
* @function			WaitForAsync
* @description		Called to wait
* @parameter		NA
* @return			NA
*/
void WaitForAsync(void)
{
	if(g_bCallbackHit != true)
	{
		g_pSyncManagerMainLoop = g_main_loop_new(NULL, false);
		int nTimeoutId = g_timeout_add(TIMEOUT, TimeoutFunction, g_pSyncManagerMainLoop);
		g_main_loop_run(g_pSyncManagerMainLoop);
		g_source_remove(nTimeoutId);
		g_pSyncManagerMainLoop = NULL;
	}
}
#if defined(MOBILE) || defined(TIZENIOT)    //Start MOBILE or TIZENIOT
/**
* @function			CreateAccount
* @description		Called to create account
* @parameter		NA
* @return			NA
*/
bool CreateAccount(void)
{
	account_h hAccount;
	int nRet = 0;

	account_connect();
	account_create(&hAccount);
	account_set_user_name(hAccount, "CoreSyncManagerTest");
	account_set_email_address(hAccount, "mymail@tizentest.com");
	account_set_package_name(hAccount, AAPID);
	account_set_sync_support(hAccount, ACCOUNT_SUPPORTS_SYNC);

	nRet = account_insert_to_db(hAccount, &g_nAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccountManagerGetError(nRet), account_destroy(hAccount); account_disconnect());
	account_destroy(hAccount);

	account_create(&g_hAccount);
	nRet = account_query_account_by_account_id(g_nAccId, &g_hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccountManagerGetError(nRet), account_destroy(g_hAccount); account_disconnect());

	account_disconnect();
	return 0;
}

/**
* @function			DeleteAccount
* @description		Called to delete account
* @parameter		NA
* @return			NA
*/
bool DeleteAccount(void)
{
	int nRet = 0;

	account_connect();
	account_destroy(g_hAccount);
	g_hAccount = NULL;

	nRet = account_delete_from_db_by_id(g_nAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_id", AccountManagerGetError(nRet), account_disconnect());

	account_disconnect();
	return 0;
}
#endif  //MOBILE or TIZENIOT

#if defined(TV) || defined(WEARABLE) //Starts TV and WEARABLEs
/**
* @function			CreateAccount
* @description		Called to create account
* @parameter		NA
* @return			NA
*/
bool CreateAccount(void)
{
	account_h hAccount;
	int nRet = 0;

	account_create(&hAccount);
	account_set_user_name(hAccount, "CoreSyncManagerTest");
	account_set_email_address(hAccount, "mymail@tizentest.com");
	account_set_package_name(hAccount, AAPID);
	account_set_sync_support(hAccount, ACCOUNT_SUPPORTS_SYNC);

	nRet = account_insert_to_db(hAccount, &g_nAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_insert_to_db", AccountManagerGetError(nRet), account_destroy(hAccount));
	account_destroy(hAccount);

	account_create(&g_hAccount);
	nRet = account_query_account_by_account_id(g_nAccId, &g_hAccount);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_query_account_by_account_id", AccountManagerGetError(nRet), account_destroy(g_hAccount));

	return 0;
}

/**
* @function			DeleteAccount
* @description		Called to delete account
* @parameter		NA
* @return			NA
*/
bool DeleteAccount(void)
{
	int nRet = 0;

	account_destroy(g_hAccount);
	g_hAccount = NULL;

	nRet = account_delete_from_db_by_id(g_nAccId);
	PRINT_RESULT_CLEANUP(ACCOUNT_ERROR_NONE, nRet, "account_delete_from_db_by_id", AccountManagerGetError(nRet), NULL);

	return 0;
}

#endif	//End WEARABLE or TV
/**
* @function			CreateBundle
* @description		Called to create bundle
* @parameter		NA
* @return			NA
*/
bool CreateBundle(void)
{
	g_pBundle = bundle_create();
	bundle_add_str(g_pBundle, BUNDLEKEY, BUNDLEVALUE);
	return 0;
}

/**
* @function			DeleteBundle
* @description		Called to delete bundle
* @parameter		NA
* @return			NA
*/
bool DeleteBundle(void)
{
	bundle_free(g_pBundle);
	g_pBundle = NULL;
	return 0;
}

/**
* @function			CreateSetup
* @description		Called to create the setup
* @parameter		NA
* @return			NA
*/
bool CreateSetup(void)
{
	g_bSetupReady = false;
	int nRet = CreateAccount();
	PRINT_RESULT(0, nRet, "CreateAccount", "Return Value Not Correct");

	nRet = CreateBundle();
	PRINT_RESULT(0, nRet, "CreateBundle", "Return Value Not Correct");

	g_bIsSyncFeatureSupported = false;
	nRet = system_info_get_platform_bool(SYNC_FEATURE, &g_bIsSyncFeatureSupported);
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRet, "system_info_get_platform_bool", "Return Value Not Correct");

	nRet = sync_adapter_set_callbacks(SyncAdapterStartCallback, SyncAdapterCancelCallback);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_adapter_set_callbacks", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(SYNC_ERROR_NONE, nRet, "sync_adapter_set_callbacks", SyncManagerGetError(nRet));
	}

	g_bSetupReady = true;
	return 0;
}

/**
* @function			DestroySetup
* @description		Called to destroy the setup
* @parameter		NA
* @return			NA
*/
bool DestroySetup(void)
{
	int nRet = -1;

	if(g_bSetupReady == true)
	{
		nRet = DeleteBundle();
		PRINT_RESULT_CLEANUP(0, nRet, "DeleteBundle", "Return Value Not Correct", DeleteAccount(); sync_adapter_unset_callbacks());

		nRet = DeleteAccount();
		PRINT_RESULT_CLEANUP(0, nRet, "DeleteAccount", "Return Value Not Correct", sync_adapter_unset_callbacks());

		nRet = sync_adapter_unset_callbacks();
		if (!g_bIsSyncFeatureSupported) {
			PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_adapter_unset_callbacks", SyncManagerGetError(nRet));
		} else {
			PRINT_RESULT(SYNC_ERROR_NONE, nRet, "sync_adapter_unset_callbacks", SyncManagerGetError(nRet));
		}
	}
	else
	{
		if(g_pBundle != NULL)
		{
			nRet = DeleteBundle();
		}

		if(g_hAccount != NULL)
		{
			nRet = DeleteAccount();
		}
	}

	return 0;
}

/** @} */
