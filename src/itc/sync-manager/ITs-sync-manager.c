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

/** @addtogroup itc-sync-manager
*  @ingroup itc
*  @{
*/

//& set: SyncManager

/*******************************************************************************CallBack Functions********************************************************/

/**
* @function			SyncAdapterStartCallback
* @description		Called when syncing starts
* @parameter		account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data
* @return			NA
*/
bool SyncAdapterStartCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SyncAdapterStartCallback callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pSyncManagerMainLoop )
	{
		g_main_loop_quit(g_pSyncManagerMainLoop);
	}
	return true;
}

/**
* @function			SyncAdapterCancelCallback
* @description		Called when syncing is cancelled
* @parameter		account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data
* @return			NA
*/
void SyncAdapterCancelCallback(account_h account, const char *sync_job_name, const char *sync_capability, bundle *sync_job_user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SyncAdapterCancelCallback callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pSyncManagerMainLoop )
	{
		g_main_loop_quit(g_pSyncManagerMainLoop);
	}
	return;
}

/**
* @function			SyncAdaptorForeachCallback
* @description		Called when syncing is cancelled
* @parameter		account_h account, const char *sync_job_name, const char * sync_capability, int sync_job_id, bundle *sync_job_user_data, void *user_data
* @return			NA
*/
static bool SyncAdaptorForeachCallback(account_h account, const char *sync_job_name, const char * sync_capability, int sync_job_id, bundle *sync_job_user_data, void *user_data)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] SyncAdaptorForeachCallback callback called\\n", __LINE__, API_NAMESPACE);
#endif
	g_bCallbackHit = true;
	if ( g_pSyncManagerMainLoop )
	{
		g_main_loop_quit(g_pSyncManagerMainLoop);
	}
	return false;
}

/*****************************************************************************End CallBack Functions******************************************************/

/**
* @function			ITs_sync_manager_startup
* @description		Called before each test
* @parameter		NA
* @return			NA
*/
void ITs_sync_manager_startup(void)
{
	struct stat stBuff;
	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}

	g_bSyncManagerInit = true;
	return;
}

/**
* @function			ITs_sync_manager_cleanup
* @description		Called after each test
* @parameter		NA
* @return			NA
*/
void ITs_sync_manager_cleanup(void)
{
	return;
}

/** @addtogroup itc-sync-manager-testcases
*  @brief		Integration testcases for module sync-manager
*  @ingroup		itc-sync-manager
*  @{
*/

/**
* @testcase				ITc_sync_manager_sync_adapter_set_unset_callbacks_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Test sync_adapter_set_callbacks and sync_adapter_unset_callbacks
* @scenario				Call sync_adapter_set_callbacks and sync_adapter_unset_callbacks
* @apicovered			sync_adapter_set_callbacks, sync_adapter_unset_callbacks
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_adapter_set_callbacks and sync_adapter_unset_callbacks
//& type: auto
int ITc_sync_manager_sync_adapter_set_unset_callbacks_p(void)
{
	START_TEST;
	int nRet = -1;

	g_bIsSyncFeatureSupported = false;
	nRet = system_info_get_platform_bool(SYNC_FEATURE, &g_bIsSyncFeatureSupported);
	PRINT_RESULT(SYSTEM_INFO_ERROR_NONE, nRet, "system_info_get_platform_bool", "Return Value Not Correct");

	nRet = sync_adapter_set_callbacks(SyncAdapterStartCallback, SyncAdapterCancelCallback);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_adapter_set_callbacks", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(SYNC_ERROR_NONE, nRet, "sync_adapter_set_callbacks", SyncManagerGetError(nRet));
	}

	nRet = sync_adapter_unset_callbacks();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_adapter_unset_callbacks", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(SYNC_ERROR_NONE, nRet, "sync_adapter_unset_callbacks", SyncManagerGetError(nRet));
	}

	return 0;
}

/**
* @testcase				ITc_sync_manager_on_demand_sync_job_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Test sync_manager_on_demand_sync_job
* @scenario				Call sync_manager_on_demand_sync_job
* @apicovered			sync_manager_on_demand_sync_job
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_manager_on_demand_sync_job
//& type: auto
int ITc_sync_manager_on_demand_sync_job_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;

	nRet = CreateSetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "CreateSetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "CreateSetup", "Return Value Not Correct");
	}

	nRet = sync_manager_on_demand_sync_job(g_hAccount, SYNCJOBNAME, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_on_demand_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_on_demand_sync_job", SyncManagerGetError(nRet), DestroySetup());

		g_bCallbackHit = false;
		WaitForAsync();
		PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "sync_manager_on_demand_sync_job", "CallBack Not Invoked", sync_manager_remove_sync_job(nSyncJobId); DestroySetup());
	}

	nRet = DestroySetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "DestroySetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "DestroySetup", "Return Value Not Correct");
	}

	return 0;
}

/**
* @testcase				ITc_sync_manager_add_remove_periodic_sync_job_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Test sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @scenario				Call sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @apicovered			sync_manager_add_periodic_sync_job, sync_manager_remove_sync_job
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
//& type: auto
int ITc_sync_manager_add_remove_periodic_sync_job_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;

	nRet = CreateSetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "CreateSetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "CreateSetup", "Return Value Not Correct");
	}

	nRet = sync_manager_add_periodic_sync_job(g_hAccount, SYNCJOBNAME, SYNC_PERIOD_INTERVAL_30MIN, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_add_periodic_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_add_periodic_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = sync_manager_remove_sync_job(nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = DestroySetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "DestroySetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "DestroySetup", "Return Value Not Correct");
	}

	return 0;
}

#if defined(MOBILE) || defined(TIZENIOT)    //Start MOBILE or TIZENIOT
/**
* @testcase				ITc_sync_manager_add_remove_data_change_sync_job_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @typea				auto
* @description			Test sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @scenario				Call sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @apicovered			sync_manager_remove_sync_job
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
//& type: auto
int ITc_sync_manager_add_remove_data_change_sync_job_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;

	nRet = CreateSetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "CreateSetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "CreateSetup", "Return Value Not Correct");
	}

	nRet = sync_manager_add_data_change_sync_job(g_hAccount, SYNC_SUPPORTS_CAPABILITY_CALENDAR, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_add_data_change_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_add_data_change_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = sync_manager_remove_sync_job(nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = DestroySetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "DestroySetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "DestroySetup", "Return Value Not Correct");
	}

	return 0;
}
#endif  //MOBILE or TIZENIOT

#if defined(TV) || defined(WEARABLE) //Starts TV and WEARABLE

/**
* @testcase				ITc_sync_manager_add_remove_data_change_sync_job_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Test sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @scenario				Call sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
* @apicovered			sync_manager_remove_sync_job
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APis sync_manager_add_periodic_sync_job and sync_manager_remove_sync_job
//& type: auto
int ITc_sync_manager_add_remove_data_change_sync_job_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;

	nRet = CreateSetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "CreateSetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "CreateSetup", "Return Value Not Correct");
	}

	nRet = sync_manager_add_data_change_sync_job(g_hAccount, SYNC_SUPPORTS_CAPABILITY_IMAGE, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_add_data_change_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_add_data_change_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = sync_manager_remove_sync_job(nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = DestroySetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "DestroySetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "DestroySetup", "Return Value Not Correct");
	}

	return 0;
}
#endif  //End WEARABLE or TV


/**
* @testcase				ITc_sync_manager_foreach_sync_job_p
* @since_tizen			2.4
* @author				SRID(abhishek1.g)
* @reviewer				SRID(gupta.sanjay)
* @type					auto
* @description			Test sync_manager_foreach_sync_job
* @scenario				Call sync_manager_foreach_sync_job
* @apicovered			sync_manager_on_demand_sync_job, sync_manager_foreach_sync_job, sync_manager_remove_sync_job
* @passcase				When API Returns SYNC_ERROR_NONE
* @failcase				If target API fails or any precondition API fails
* @precondition			None
* @postcondition		None
*/
//& purpose: Test APi sync_manager_foreach_sync_job
//& type: auto
int ITc_sync_manager_foreach_sync_job_p(void)
{
	START_TEST;
	int nRet = -1;
	int nSyncJobId = 0;

	nRet = CreateSetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "CreateSetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "CreateSetup", "Return Value Not Correct");
	}

	nRet = sync_manager_add_periodic_sync_job(g_hAccount, SYNCJOBNAME, SYNC_PERIOD_INTERVAL_30MIN, SYNC_OPTION_NONE, g_pBundle, &nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_add_periodic_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_add_periodic_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	g_bCallbackHit = false;
	nRet = sync_manager_foreach_sync_job(SyncAdaptorForeachCallback, NULL);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_foreach_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_foreach_sync_job", SyncManagerGetError(nRet), sync_manager_remove_sync_job(nSyncJobId); DestroySetup());
		WaitForAsync();
		PRINT_RESULT_CLEANUP(true, g_bCallbackHit, "sync_manager_foreach_sync_job", "CallBack Not Invoked", sync_manager_remove_sync_job(nSyncJobId); DestroySetup());
	}

	nRet = sync_manager_remove_sync_job(nSyncJobId);
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NOT_SUPPORTED, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	} else {
		PRINT_RESULT_CLEANUP(SYNC_ERROR_NONE, nRet, "sync_manager_remove_sync_job", SyncManagerGetError(nRet), DestroySetup());
	}

	nRet = DestroySetup();
	if (!g_bIsSyncFeatureSupported) {
		PRINT_RESULT(SYNC_ERROR_NOT_SUPPORTED, nRet, "DestroySetup", SyncManagerGetError(nRet));
	} else {
		PRINT_RESULT(0, nRet, "DestroySetup", "Return Value Not Correct");
	}

	return 0;
}

/** @} */
/** @} */
