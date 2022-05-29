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
* @function 		ITs_contacts_service2_activity_startup
* @description	 	Called before each test, set the service boolean true
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_activity_startup(void)
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
		if ( ContactsServiceCreateAndInsertRecord(&g_nFirstRecordId, &g_nFirstContactId, &g_nFirstPersonId, &g_hFirstProfileRecord, &g_hRecordFirst, "099882721", "TESTFIRST_a") == true )
		{
			g_bContactsServiceCreation = true;
		}
		else
		{
			g_bContactsServiceCreation = false;
		}
	}
	else
	{
		g_bContactsServiceCreation = false;
	}
	return;
}

/**
* @function 		ITs_contacts_service2_activity_cleanup
* @description	 	Called after each test
* @parameter		NA
* @return 			NA
*/
void ITs_contacts_service2_activity_cleanup(void)
{
#if DEBUG
	FPRINTF("[Line : %d][%s] TEST SUIT clean-up: ITs_Contacts_Service2_p\\n", __LINE__, API_NAMESPACE);
#endif
	contacts_record_destroy(g_hRecordFirst, true);
	contacts_record_destroy(g_hFirstProfileRecord, true);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstRecordId);
	contacts_db_delete_record(_contacts_contact._uri, g_nFirstContactId);
	contacts_db_delete_record(_contacts_person._uri, g_nFirstPersonId);
	ContactsServiceDisconnect();
	sleep(SLEEP_TIME);
	return;
}

/** @addtogroup itc-contacts_service2-activity-testcases
*  @brief 		Integration testcases for module contacts_service2-activity
*  @ingroup 	itc-contacts_service2-activity
*  @{
*/

//& purpose: Deletes an activity record from the contacts database by account id..
//& type: auto

/**
* @testcase 			ITc_contacts_activity_delete_by_account_id_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Deletes an activity record from the contacts database by account id.
* @scenario				Deletes an activity record
* @apicovered			contacts_activity_delete_by_account_id()
* @passcase				When contacts_activity_delete_by_account_id() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service
* @postcondition		None
*/
int ITc_contacts_activity_delete_by_account_id_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_activity_delete_by_account_id(g_nFirstRecordId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_activity_delete_by_account_id", ContactsServiceGetError(nRet));

	return 0;
}

//& purpose: Deletes an activity record from the contacts database by contact id.
//& type: auto

/**
* @testcase 			ITc_contacts_activity_delete_by_contact_id_p
* @since_tizen			2.3
* @author            	SRID(sk.roy)
* @reviewer         	SRID(gupta.sanjay)
* @type 				auto
* @description			Deletes an activity record from the contacts database by contact id
* @scenario				Deletes an activity record from contact database.
* @apicovered			contacts_activity_delete_by_contact_id()
* @passcase				When contacts_activity_delete_by_contact_id() is successful.
* @failcase				If target API fails or any precondition API fails.
* @precondition			contacts_connect2() should be called to open a connection to the contacts service.e
* @postcondition		None
*/
int ITc_contacts_activity_delete_by_contact_id_p(void)
{
	START_TEST;

	// Target API
	int nRet = contacts_activity_delete_by_contact_id(g_nFirstContactId);
	PRINT_RESULT(CONTACTS_ERROR_NONE, nRet, "contacts_activity_delete_by_contact_id", ContactsServiceGetError(nRet));

	return 0;
}
/** @} */ 
/** @} */
