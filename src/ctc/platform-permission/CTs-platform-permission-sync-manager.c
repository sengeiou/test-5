#include <sync_manager.h>
#include <sync_adapter.h>
#include <sync-error.h>
#include "CTs-platform-permission-common.h"

#define BUNDLEKEY                               "str"
#define BUNDLEVALUE                             "String user_data sample."
#define AAPID                                   "org.tizen.sync-manager-native-itc"
#define SYNCJOBNAME                             "syncjob"


bool DestroySetup(void);
bool CreateSetup(void);
bool DeleteAccount(void);
bool CreateAccount(void);
char* SyncManagerGetError(int nRet);
void SyncAdapterCancelCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data);
bool SyncAdapterStartCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data);
bool g_bCallbackHit;
GMainLoop *g_pSyncManagerMainLoop;
account_h g_hAccount;
bundle *g_pBundle;
int g_nAccId;
bool g_bSetupReady;
/**
* @function 		SyncManagerGetError
* @description	 	Maps error enums to string values
* @parameter		nRet : error code returned
* @return 			error string
*/
char* SyncManagerGetError(int nRet)
{
	char *szErrorVal = "SYNC_ERROR_UNKNOWN";
	switch ( nRet )
	{
		case SYNC_ERROR_NONE:						szErrorVal = "SYNC_ERROR_NONE";							break;
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
	}

	return szErrorVal;
}
/**
* @function 		CTs_platform_permission_syncmanager_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_syncmanager_startup(void)
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
* @function 		CTs_platform_permission_syncmanager_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void CTs_platform_permission_syncmanager_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: CTs_Platform_Permission_p\\n", __LINE__, API_NAMESPACE);
#endif
	return;
}

/**
* @function             CreateAccount
* @description          Called to create account
* @parameter            NA
* @return                       NA
*/
bool CreateAccount(void)
{
        account_h hAccount;
        
        account_connect();
        account_create(&hAccount);
        account_set_user_name(hAccount, "CoreSyncManagerTest");
        account_set_email_address(hAccount, "mymail@tizentest.com");
        account_set_package_name(hAccount, AAPID);
        account_set_sync_support(hAccount, ACCOUNT_SUPPORTS_SYNC);

        account_insert_to_db(hAccount, &g_nAccId);
        account_destroy(hAccount);

        account_create(&g_hAccount);
        account_query_account_by_account_id(g_nAccId, &g_hAccount);
       
        account_disconnect();
        return 0;
}
/**
* @function             DeleteAccount
* @description          Called to delete account
* @parameter            NA
* @return                       NA
*/
bool DeleteAccount(void)
{
        account_connect();
        account_destroy(g_hAccount);
        g_hAccount = NULL;

        account_delete_from_db_by_id(g_nAccId);
       
        account_disconnect();
        return 0;
}
/**
* @function             CreateBundle
* @description          Called to create bundle
* @parameter            NA
* @return                       NA
*/
bool CreateBundle(void)
{
        g_pBundle = bundle_create();
        bundle_add_str(g_pBundle, BUNDLEKEY, BUNDLEVALUE);
        return 0;
}

/**
* @function             DeleteBundle
* @description          Called to delete bundle
* @parameter            NA
* @return                       NA
*/
bool DeleteBundle(void)
{
        bundle_free(g_pBundle);
        g_pBundle = NULL;
        return 0;
}
/**
* @function             CreateSetup
* @description          Called to create the setup
* @parameter            NA
* @return                       NA
*/
bool CreateSetup(void)
{
        g_bSetupReady = false;
        CreateAccount();
        
        CreateBundle();
        
        sync_adapter_set_callbacks(SyncAdapterStartCallback, SyncAdapterCancelCallback);
        
        g_bSetupReady = true;
        return 0;
}

/**
* @function             DestroySetup
* @description          Called to destroy the setup
* @parameter            NA
* @return                       NA
*/
bool DestroySetup(void)
{
        if(g_bSetupReady == true)
        {
        	DeleteBundle();
                DeleteAccount();
               	sync_adapter_unset_callbacks();
}
        else
        {
                if(g_pBundle != NULL)
                {
                	DeleteBundle();
                }

                if(g_hAccount != NULL)
                {
                        DeleteAccount();
                }
        }

        return 0;
}
/**
* @function 		SyncAdapterStartCallback
* @description	 	Called when syncing starts
* @parameter		account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data
* @return 			NA
*/
bool SyncAdapterStartCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SyncAdapterStartCallback callback called\\n", __LINE__, API_NAMESPACE);
#endif
	return true;
	
}

/**
* @function 		SyncAdapterCancelCallback
* @description	 	Called when syncing is cancelled
* @parameter		account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data
* @return 			NA
*/
void SyncAdapterCancelCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SyncAdapterCancelCallback callback called\\n", __LINE__, API_NAMESPACE);
#endif
	
}
//& purpose:Checking tizen.org/privilege/alarm.set privilege
//& type: auto
/**
* @testcase			CTc_SyncManager_PrivilegeAlarmSet
* @since_tizen		2.4
* @author			SRID(manoj.g2)
* @reviewer			SRID(shobhit.v)
* @type 			auto
* @scenario			Gets the volume level specified for a particular sound type\n
*					Sets the volume level specified for a particular sound type
* @apicovered		sound_manager_get_volume and sound_manager_set_volume
* @passcase			If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase			If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition		NA
* @postcondition	NA
*/
int CTc_SyncManager_PrivilegeAlarmSet(void)
{
        START_TEST;
        int nRet = -1;
        int nSyncJobId = 0;
		nRet = account_create(&g_hAccount);
		PRINT_RESULT(SYNC_ERROR_NONE, nRet, "account_create", "Return Value Not Correct");
		
		g_pBundle = bundle_create();
		nRet = get_last_result();
		PRINT_RESULT(SYNC_ERROR_NONE, nRet, "bundle_create", "Return Value Not Correct");
		
        bundle_add_str(g_pBundle, BUNDLEKEY, BUNDLEVALUE);
        nRet = sync_manager_add_periodic_sync_job(g_hAccount, SYNCJOBNAME, SYNC_PERIOD_INTERVAL_30MIN, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
		PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "sync_manager_add_periodic_sync_job", SyncManagerGetError(nRet), bundle_free(g_pBundle);account_destroy(g_hAccount));
		
        return 0;
}
/**
* @testcase 			CTc_SyncManager_PrivilegeContactRead_PrivilegeCalendarRead
* @since_tizen 			2.4
* @author				SRID(manoj.g2)
* @reviewer				SRID(shobhit.v)
* @type 				auto
* @description			Test sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @scenario				Call sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @apicovered			sync_manager_remove_sync_job
* @passcase				If target privileged API returns TIZEN_ERROR_PERMISSION_DENIED
* @failcase				If target privileged API does not return TIZEN_ERROR_PERMISSION_DENIED
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
//& type: auto
int CTc_SyncManager_PrivilegeContactRead_PrivilegeCalendarRead(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;
	nRet = account_create(&g_hAccount);
	PRINT_RESULT(SYNC_ERROR_NONE, nRet, "account_create", "Return Value Not Correct");
	
	g_pBundle = bundle_create();
	nRet = get_last_result();
	PRINT_RESULT(SYNC_ERROR_NONE, nRet, "bundle_create", "Return Value Not Correct");
	
	bundle_add_str(g_pBundle, BUNDLEKEY, BUNDLEVALUE);
	nRet = sync_manager_add_data_change_sync_job(g_hAccount, SYNC_SUPPORTS_CAPABILITY_CALENDAR, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	PRINT_RESULT_CLEANUP(TIZEN_ERROR_PERMISSION_DENIED, nRet, "sync_manager_add_data_change_sync_job", SyncManagerGetError(nRet), bundle_free(g_pBundle);account_destroy(g_hAccount));
	
	return 0;
}
