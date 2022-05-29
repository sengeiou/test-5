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
#include "ITs-contacts-service2-common.h"

/** @addtogroup itc-contacts-service2
*  @ingroup itc
*  @{
*/

//& set: ContactsService

bool g_bFeatureIsSupported = false;

/**
* @function 		ITs_contacts_service2_sim_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/

static bool _import_progress_cb(int total, int imported_cnt, void *user_data)
{	
	FPRINTF("[Line : %d][%s] _import_progress_cb callback called\\n", __LINE__, API_NAMESPACE);
	g_bCallbackHit = true;
	return false;
}

void ITs_contacts_service2_sim_startup(void)
{
	struct stat stBuff;
	g_bFeatureIsSupported = false;
	g_bIsContactFeatureSupported = false;
	g_bContactFeatureMismatch = false;
	g_bIsConnected = false;

	if ( stat(ERR_LOG, &stBuff) == 0 )
	{
		remove(ERR_LOG);
	}	
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT start-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif

	g_bIsContactFeatureSupported = TCTCheckSystemInfoFeatureSupported(CONTACT_FEATURE, API_NAMESPACE);

	g_bFeatureIsSupported = g_bIsContactFeatureSupported && TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);

	if ( ContactsServiceConnect() == true )
	{
		g_bContactsServiceCreation = true;
	}
	else
	{
		g_bContactsServiceCreation = false;
	}
	return;
}

/**
* @function 		ITs_contacts_service2_sim_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_sim_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-testcases-sim
*  @brief 		Integration testcases for module contacts_service2-sim
*  @ingroup 	itc-contacts_service2-sim
*  @{
*/

//& purpose: Checks whether SIM of the given SIM slot number is initialized
//& type: auto

/**
* @testcase 			ITc_contacts_sim_get_initialization_status_by_sim_slot_no_p
* @since_tizen			3.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shilpa.j)
* @type 				auto
* @description			Checks whether SIM of the given SIM slot number is initialized
* @scenario				Telephony init\n
*						Check initialization status\n
* 						Telephony deinit
* @apicovered			contacts_sim_get_initialization_status_by_sim_slot_no
* @passcase				When contacts_sim_get_initialization_status_by_sim_slot_no is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			telephony_init should be called as precondition API
* @postcondition		None
*/
int ITc_contacts_sim_get_initialization_status_by_sim_slot_no_p(void)
{
	START_TEST;
	telephony_handle_list_s hTelList;
	int nSimSlotNo = 0;
	bool bInitComplete = false;
	
	int nRet = telephony_init(&hTelList);
	if(!g_bFeatureIsSupported)
	{
		if(nRet != TIZEN_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] telephony_init API call did not return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] telephony_init API call correctly return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_init", "Telephony Api Failed");
	
	for (nSimSlotNo = 0; nSimSlotNo < hTelList.count; nSimSlotNo++) 
	{
		nRet = contacts_sim_get_initialization_status_by_sim_slot_no(nSimSlotNo, &bInitComplete);
		if ( !g_bFeatureIsSupported )
		{		
			telephony_deinit(&hTelList);
			if(nRet != TIZEN_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line : %d][%s] contacts_sim_get_initialization_status_by_sim_slot_no API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] Telephony feature is not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}
		PRINT_RESULT_CLEANUP(CONTACTS_ERROR_NONE, nRet, "contacts_sim_get_initialization_status_by_sim_slot_no", 
							 ContactsServiceGetError(nRet), telephony_deinit(&hTelList));
		if ( bInitComplete == false )
		{
			FPRINTF("[Line : %d][%s] Sim not initialized for slot number = %d\\n", __LINE__ , API_NAMESPACE, nSimSlotNo);
		}
	}
	telephony_deinit(&hTelList);
	return 0;
}

//& purpose: Imports all contacts from SIM of the given SIM slot number to Contacts Database.
//& type: auto

/**
* @testcase 			ITc_contacts_sim_import_all_contacts_by_sim_slot_no_p
* @since_tizen			3.0
* @author            	SRID(a.pandia1)
* @reviewer         	SRID(shilpa.j)
* @type 				auto
* @description			Imports all contacts from SIM of the given SIM slot number to Contacts Database.
* @scenario				Telephony init\n
*						Imports contacts from SIM slot number\n
* 						Telephony deinit
* @apicovered			contacts_sim_import_all_contacts_by_sim_slot_no
* @passcase				When contacts_sim_import_all_contacts_by_sim_slot_no is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			telephony_init should be called as precondition API
* @postcondition		None
*/
int ITc_contacts_sim_import_all_contacts_by_sim_slot_no_p(void)
{
	START_TEST;
	telephony_handle_list_s hTelList;
	int nSimSlotNo = 0;

	int nRet = telephony_init(&hTelList);
	if(!g_bFeatureIsSupported)
	{
		if(nRet != TIZEN_ERROR_NOT_SUPPORTED)
		{
			FPRINTF("[Line : %d][%s] telephony_init API call did not return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] telephony_init API call correctly return 'UNSUPPORTED' error for unsupported feature\\n", __LINE__, API_NAMESPACE);
			return 0;
		}
	}

	PRINT_RESULT(TELEPHONY_ERROR_NONE, nRet, "telephony_init", "Telephony Api Failed");
	
	for (nSimSlotNo = 0; nSimSlotNo < hTelList.count; nSimSlotNo++) 
	{
		g_bCallbackHit = false;
		nRet = contacts_sim_import_all_contacts_by_sim_slot_no(nSimSlotNo, _import_progress_cb, NULL);
		if ( !g_bFeatureIsSupported )
		{		
			telephony_deinit(&hTelList);
			if(nRet != TIZEN_ERROR_NOT_SUPPORTED)
			{
				FPRINTF("[Line : %d][%s] contacts_sim_import_all_contacts_by_sim_slot_no API call returned mismatch %s error for unsupported feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
				return 1;
			}
			else
			{
				FPRINTF("[Line : %d][%s] Telephony feature is not supported, Leaving test\\n", __LINE__, API_NAMESPACE);
				return 0;
			}
		}

		if ((CONTACTS_ERROR_NONE != nRet && CONTACTS_ERROR_NO_DATA != nRet)
#ifdef MOBILE
			|| (CONTACTS_ERROR_NO_DATA == nRet && 0 == nSimSlotNo )
#endif
			|| (CONTACTS_ERROR_NONE == nRet && g_bCallbackHit == false))
		{
				FPRINTF("[Line : %d][%s] contacts_sim_import_all_contacts_by_sim_slot_no failed, error returned = %s [%d]\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet), nRet);
				telephony_deinit(&hTelList);
				return 1;
		}
	}
	telephony_deinit(&hTelList);
	
	return 0;
}

/** @} */ 
/** @} */
