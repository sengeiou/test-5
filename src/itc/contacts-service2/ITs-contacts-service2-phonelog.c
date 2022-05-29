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

/**
* @function 		ITs_contacts_service2_phonelog_startup
* @description	 	Called before each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_phonelog_startup(void)
{
	struct stat stBuff;
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
* @function 		ITs_contacts_service2_phonelog_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_phonelog_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-phonelog-testcases
*  @brief 		Integration testcases for module contacts_service2-phonelog
*  @ingroup 	itc-contacts_service2-phonelog
*  @{
*/

//& purpose: Resets the phone log's count.
//& type: auto

/**
* @testcase 			ITc_contacts_phone_log_reset_statistics_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Resets the phone log's count.
* @scenario				Connect to database\n
*						Reset the phone log's count\n
* 						Disconnect from database
* @apicovered			contacts_phone_log_reset_statistics()
* @passcase				When contacts_phone_log_reset_statistics() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_phone_log_reset_statistics_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_phone_log_reset_statistics();
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_phone_log_reset_statistics", ContactsServiceGetError(nRet));

	return 0;

}

//& purpose: Resets the phone log's count by sim slot no.
//& type: auto
/**
* @testcase        ITc_contacts_phone_log_reset_statistics_by_sim_p
* @since_tizen     3.0
* @author          SRID(nibha.sharma)
* @reviewer        SRID(parshant.v)	
* @type            auto	
* @description     Resets the phone log's count by sim slot no.	
* @scenario        Connect to database\n	
*              	   Reset the phone log's count by sim slot no.\n	
*                  Disconnect from database	
* @apicovered      contacts_phone_log_reset_statistics_by_sim	
* @passcase        When contacts_phone_log_reset_statistics_by_sim is successful.	
* @failcase        If target API fails or any precondition API fails.	
* @precondition    contacts_connect2() should be called to open a connection to the contacts service.e	
* @postcondition   None	
*/	
int ITc_contacts_phone_log_reset_statistics_by_sim_p(void)	
{	

   START_TEST;	
   bool bIsTelephonyFeatureIsSupported = true;
   bIsTelephonyFeatureIsSupported = TCTCheckSystemInfoFeatureSupported(TELEPHONY_FEATURE, API_NAMESPACE);
   
   //nSimSlotNo 0 means first SIM, nSimSlotNo 1 means second SIM 	
   int nSimSlotNo = 0;	
	
   // Target API
   int nRet = contacts_phone_log_reset_statistics_by_sim(nSimSlotNo);	
   
   if(!bIsTelephonyFeatureIsSupported)
   {
		if ( nRet != TIZEN_ERROR_NOT_SUPPORTED )
		{
			FPRINTF("[Line : %d][%s] contacts_phone_log_reset_statistics_by_sim API call returned mismatch %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 1;
		}
		else
		{
			FPRINTF("[Line : %d][%s] contacts_phone_log_reset_statistics_by_sim API call correctly returned %s error for unsupported telephony feature\\n", __LINE__, API_NAMESPACE, ContactsServiceGetError(nRet));
			return 0;
		}
   }

   PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_phone_log_reset_statistics_by_sim", ContactsServiceGetError(nRet));	
   return 0;	
}

/** @} */ 
/** @} */
